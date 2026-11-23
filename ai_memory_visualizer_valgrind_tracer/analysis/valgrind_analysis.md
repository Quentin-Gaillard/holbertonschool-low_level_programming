# Valgrind & Memory Lifetime Analysis

## 0. Executive Summary

| Program | Total Heap Usage | Memory Leaks (`in use at exit`) | Memory Access Errors | Root Cause |
| :--- | :--- | :--- | :--- | :--- |
| **`heap_example`** | 5 allocs, 4 frees (1,066 bytes) | **6 bytes in 1 block (`definitely lost`)** | 0 errors | Incomplete cleanup of nested heap allocations (`alice` was freed without freeing `alice->name` first). |
| **`aliasing_example`** | 2 allocs, 2 frees (1,044 bytes) | **0 bytes (`no leaks are possible`)** | **3 errors** (2 `Invalid read`, 1 `Invalid write`) | Pointer aliasing (`b = a`) followed by `free(a)` turned `b` into a dangling pointer; subsequent reads/writes caused **Use-After-Free**. |

---

## 1. `heap_example.c` Analysis

### Valgrind Output Summary
```text
heap_example: allocations and a deliberate leak
  alice=0x4a91480 name=0x4a914d0 age=30
  bob=0x4a91520 name=0x4a91570 age=41
==2881== HEAP SUMMARY:
==2881==     in use at exit: 6 bytes in 1 blocks
==2881==   total heap usage: 5 allocs, 4 frees, 1,066 bytes allocated
==2881== 6 bytes in 1 blocks are definitely lost in loss record 1 of 1
==2881==    at 0x4850858: malloc (vg_replace_malloc.c:447)
==2881==    by 0x4001211: person_new (heap_example.c:21)
==2881==    by 0x40012FA: main (heap_example.c:51)
==2881== LEAK SUMMARY:
==2881==    definitely lost: 6 bytes in 1 blocks
==2881==    indirectly lost: 0 bytes in 0 blocks
==2881==      possibly lost: 0 bytes in 0 blocks
==2881==    still reachable: 0 bytes in 0 blocks
==2881== ERROR SUMMARY: 1 errors from 1 contexts
```

### Root Cause & Lifetime Breakdown
* **Allocation Accounting (5 allocs, 4 frees):**
  * 4 allocations belong to program data structures: `alice` (`0x4a91480`), `alice->name` (`0x4a914d0`, 6 bytes for `"Alice\0"`), `bob` (`0x4a91520`), and `bob->name` (`0x4a91570`, 4 bytes for `"Bob\0"`).
  * 1 allocation (1,024 bytes) is internal to `glibc`'s `printf` stdout buffer, which is automatically freed at process exit.
* **Classification — `Definitely Lost` (6 bytes in 1 block):**
  * Inside `person_new` (`heap_example.c:21`), called from `main` (`heap_example.c:51`), 6 bytes were dynamically allocated on the Heap for `alice->name` (`0x4a914d0`).
  * While `bob` and `bob->name` were properly freed in reverse allocation order, only the outer `alice` struct (`0x4a91480`) was freed—or the pointer to `alice->name` was overwritten/dropped without calling `free(alice->name)`.
  * **Lifetime Violation:** Once `alice` was freed, no valid pointer in the program still held the address `0x4a914d0`. Because the heap block remained allocated until program termination with zero surviving references, Valgrind classifies it as **`definitely lost`**.

---

## 2. `aliasing_example.c` Analysis

### Valgrind Output Summary
```text
aliasing_example: aliasing and use-after-free (Valgrind should report it)
  a=0x4a91480 b=0x4a91480 a[2]=22 b[2]=22
  after free(a): b=0x4a91480 (dangling)
==3012== Invalid read of size 4
==3012==    at 0x40012F2: main (aliasing_example.c:42)
==3012==  Address 0x4a91488 is 8 bytes inside a block of size 20 free'd
==3012==    at 0x48538BF: free (vg_replace_malloc.c:990)
==3012==    by 0x40012CE: main (aliasing_example.c:38)
==3012==  Block was alloc'd at
==3012==    at 0x4850858: malloc (vg_replace_malloc.c:447)
==3012==    by 0x40011E4: make_numbers (aliasing_example.c:12)
==3012==    by 0x4001272: main (aliasing_example.c:30)
==3012== Invalid write of size 4
==3012==    at 0x4001312: main (aliasing_example.c:44)
==3012==  Address 0x4a9148c is 12 bytes inside a block of size 20 free'd
==3012==    by 0x40012CE: main (aliasing_example.c:38)
==3012== Invalid read of size 4
==3012==    at 0x4001320: main (aliasing_example.c:45)
==3012==  Address 0x4a9148c is 12 bytes inside a block of size 20 free'd
==3012==    by 0x40012CE: main (aliasing_example.c:38)
==3012== HEAP SUMMARY:
==3012==     in use at exit: 0 bytes in 0 blocks
==3012==   total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated
==3012== All heap blocks were freed -- no leaks are possible
==3012== ERROR SUMMARY: 3 errors from 3 contexts
```

### Root Cause & Error Classification
* **Allocation & Aliasing (`aliasing_example.c:12` & `30`):**
  * `make_numbers` allocates a 20-byte heap block (`5 * sizeof(int)`) at `0x4a91480` and returns it to pointer `a` on `main`'s stack.
  * Assigning `b = a` creates an **alias**: both stack pointers store `0x4a91480` and reference the exact same heap allocation.
* **Premature End of Heap Lifetime (`aliasing_example.c:38`):**
  * `free(a)` deallocates the 20-byte block at `0x4a91480`. The heap block's valid lifetime ends at line 38, but `b` is never set to `NULL` and remains a **dangling pointer** holding `0x4a91480`.
* **Three Distinct Use-After-Free Violations:**
  1. **Error 1 — `Invalid read of size 4` (`aliasing_example.c:42`):** Dereferencing `b[2]` reads 4 bytes at `0x4a91488` (`base + 8 bytes`) inside the already-freed 20-byte chunk.
  2. **Error 2 — `Invalid write of size 4` (`aliasing_example.c:44`):** Assigning `b[3] = 1234` writes 4 bytes at `0x4a9148c` (`base + 12 bytes`) into freed heap memory, corrupting allocator-managed space.
  3. **Error 3 — `Invalid read of size 4` (`aliasing_example.c:45`):** Printing `b[3]` reads back those 4 bytes from `0x4a9148c` after the block was freed.
* **Key Takeaway:** Having `0 bytes in 0 blocks` at exit ("no leaks") does **not** mean a program is memory-safe; `aliasing_example` frees all heap memory properly once, yet commits three critical undefined-behavior accesses via a dangling alias.

---

## 3. Critical AI Review (Correction of AI Output)

### Initial AI Assumption / Error
> Before inspecting the Valgrind trace of `aliasing_example.c`, the AI assumed from the printed output (`a[2]=22`, `b[3]=1234`) that `make_numbers` allocated **16 bytes (`4 * sizeof(int)`)** on the Heap, and only identified two Use-After-Free operations (`b[2]` read and `b[3]` write).

### Why It Was Inaccurate
1. **Wrong Allocation Size:** Valgrind's exact heap report (`total heap usage: 2 allocs, 2 frees, 1,044 bytes allocated`, minus 1,024 bytes for `printf`'s buffer, plus Valgrind's explicit message *"inside a block of size 20 free'd"*) proved that `make_numbers` (`aliasing_example.c:12`) actually allocated **20 bytes (`5 * sizeof(int)`)**, not 16 bytes.
2. **Missed Third Memory Violation:** In addition to reading `b[2]` at line 42 and writing `b[3] = 1234` at line 44, line 45 immediately reads `b[3]` back inside `printf`, triggering a **third distinct Valgrind error (`Invalid read of size 4` at `0x4a9148c`)**.

### Corrected Explanation
* Always rely on Valgrind's exact byte offsets and context count (`3 errors from 3 contexts` inside a `20-byte` block allocated at `aliasing_example.c:12` and freed at `aliasing_example.c:38`) rather than inferring buffer sizes solely from the highest array index accessed in `printf`.


## What I Learned From These Valgrind Traces

Running both programs through Valgrind showed me that **two programs can look completely fine in the terminal while hiding very different memory bugs**:

1. **In `heap_example.c` (Memory Leak — `definitely lost`):**
   * Even though the program printed the right names and ages without crashing, Valgrind caught **6 bytes `definitely lost`** (`alice->name` at `0x4a914d0`, allocated in `person_new` at line 21).
   * What happened is a classic ownership mistake with nested heap allocations: `alice` was freed, but its inner string pointer (`alice->name`) was not freed first. Once the `alice` struct was freed, the address of `"Alice"` was lost forever, leaving 6 bytes stuck on the Heap until the program exited.

2. **In `aliasing_example.c` (Use-After-Free — `Invalid read` / `Invalid write`):**
   * Here, Valgrind reported **0 memory leaks** (`All heap blocks were freed`), which at first glance looks clean. However, it caught **3 serious memory errors** (`Invalid read` at lines 42 and 45, and `Invalid write` at line 44).
   * Because `b = a` only copied the heap address (`0x4a91480`) instead of creating a new array, calling `free(a)` at line 38 ended the lifetime of that 20-byte block for **both** pointers. `b` became a **dangling pointer**, so reading `b` and writing `b = 1234` accessed memory that no longer belonged to the program.

**Main takeaway:** A program with zero leaks can still corrupt memory (`aliasing_example`), and a program that does not crash can still leak heap blocks (`heap_example`). Always free inner pointers before freeing the parent struct, and set pointers to `NULL` right after calling `free()`.

