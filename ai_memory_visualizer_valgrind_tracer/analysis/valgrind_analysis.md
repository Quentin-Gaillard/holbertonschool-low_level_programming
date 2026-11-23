# Valgrind and Memory Lifetime Analysis

## 1. heap_example.c

Valgrind summary:
- Total heap usage: 5 allocs, 4 frees, 1,066 bytes allocated
- In use at exit: 6 bytes in 1 block (classified as definitely lost)
- Error summary: 1 error from 1 context

What happened in memory:
The program makes 4 allocations for its own data: alice (0x4a91480), alice->name (0x4a914d0, 6 bytes for "Alice\0"), bob (0x4a91520), and bob->name (0x4a91570, 4 bytes for "Bob\0"). The 5th allocation (1,024 bytes) is just the internal stdout buffer used by printf, which gets freed automatically at exit.

The bug is a classic ownership mistake with nested heap allocations. In person_new (heap_example.c:21, called from main at line 51), 6 bytes are allocated on the heap for alice->name. Later, bob and bob->name are both properly freed, so no memory is leaked there. However, alice is freed without freeing alice->name first. Once the alice struct is freed, the pointer holding the address 0x4a914d0 is gone, so those 6 bytes remain stuck on the heap until the program ends. Because no pointer references that block anymore, Valgrind marks it as definitely lost.

---

## 2. aliasing_example.c

Valgrind summary:
- Total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated
- In use at exit: 0 bytes in 0 blocks (no leaks are possible)
- Error summary: 3 errors from 3 contexts (two Invalid read of size 4, one Invalid write of size 4)

What happened in memory:
In make_numbers (aliasing_example.c:12, called from main at line 30), malloc allocates a 20-byte block (5 integers) on the heap at address 0x4a91480 and stores that address in stack pointer a. Then b = a copies the address into stack pointer b, creating an alias. Both pointers now point to the exact same heap block.

At line 38, free(a) releases that 20-byte block back to the allocator. The lifetime of the heap memory ends right there, but b still holds the old address 0x4a91480, making b a dangling pointer. After that point, the program triggers three Use-After-Free errors:
1. Line 42: Invalid read of size 4 at 0x4a91488 (8 bytes inside the freed 20-byte block) when reading b[2].
2. Line 44: Invalid write of size 4 at 0x4a9148c (12 bytes inside the freed 20-byte block) when writing b[3] = 1234.
3. Line 45: Invalid read of size 4 at 0x4a9148c when printing b[3].

Even though Valgrind says all heap blocks were freed and there are zero leaks, the program still corrupts freed memory because it keeps using an alias after the owner freed the block.

---

## 3. Critical AI Review

Initial AI assumption:
Before looking at the Valgrind output for aliasing_example.c, the AI guessed from the printed output (a[2]=22 and b[3]=1234) that make_numbers allocated 16 bytes (4 integers) on the heap, and only mentioned two Use-After-Free accesses (one read and one write).

Why it was wrong:
Valgrind showed 1,044 bytes allocated in total (1,024 bytes for printf plus 20 bytes for make_numbers) and explicitly reported "a block of size 20 free'd", meaning the array actually had 5 integers, not 4. It also caught a third invalid access at line 45 when printf reads b[3] right after writing to it. This showed that you cannot guess exact allocation sizes or error counts just from program output without checking Valgrind's byte offsets.

---

## 4. What I Learned

Running both programs under Valgrind showed me that a program can look fine in the terminal while still having serious memory bugs:
- A program that does not crash can still leak memory if nested heap pointers are not freed before their parent struct (heap_example.c).
- A program with zero memory leaks can still have undefined behavior if two pointers share the same heap address and one of them is used after free() (aliasing_example.c).

To avoid these issues, inner heap pointers must always be freed before the outer struct, and pointers should be set to NULL right after calling free().
