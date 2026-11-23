## 1. `stack_example.c`

### Execution Output
```text
stack_example: recursion and stack frames
[enter] depth=0
  &local_int=0x7ffcdb861334  p_local=0x7ffcdb861334  local_int=100
  local_buf=0x7ffcdb861340  local_buf[0]=A
  &marker=0x7ffcdb861384  marker=0
[enter] depth=1
  &local_int=0x7ffcdb861304  p_local=0x7ffcdb861304  local_int=101
  local_buf=0x7ffcdb861310  local_buf[0]=B
  &marker=0x7ffcdb861354  marker=10
[enter] depth=2
  &local_int=0x7ffcdb8612d4  p_local=0x7ffcdb8612d4  local_int=102
  local_buf=0x7ffcdb8612e0  local_buf[0]=C
  &marker=0x7ffcdb861324  marker=20
[enter] depth=3
  &local_int=0x7ffcdb8612a4  p_local=0x7ffcdb8612a4  local_int=103
  local_buf=0x7ffcdb8612b0  local_buf[0]=D
  &marker=0x7ffcdb8612f4  marker=30
[exit] depth=3
  &local_int=0x7ffcdb8612a4  p_local=0x7ffcdb8612a4  local_int=103
  local_buf=0x7ffcdb8612b0  local_buf[0]=D
  &marker=0x7ffcdb8612f4  marker=30
[exit] depth=2
  &local_int=0x7ffcdb8612d4  p_local=0x7ffcdb8612d4  local_int=102
  local_buf=0x7ffcdb8612e0  local_buf[0]=C
  &marker=0x7ffcdb861324  marker=20
[exit] depth=1
  &local_int=0x7ffcdb861304  p_local=0x7ffcdb861304  local_int=101
  local_buf=0x7ffcdb861310  local_buf[0]=B
  &marker=0x7ffcdb861354  marker=10
[exit] depth=0
  &local_int=0x7ffcdb861334  p_local=0x7ffcdb861334  local_int=100
  local_buf=0x7ffcdb861340  local_buf[0]=A
  &marker=0x7ffcdb861384  marker=0
```

### Step-by-Step Memory Map (Stack vs Heap)
* **Heap Memory:** `0 bytes` allocated. This program never calls `malloc`, `calloc`, or `realloc`. All data resides exclusively on the **Stack**.
* **Stack Growth Direction:** On this x86_64 architecture, the stack grows downward toward lower memory addresses. Each recursive call to `walk_stack` allocates a new 48-byte (`0x30`) stack frame:
  * `walk_stack(0, 3)` frame: `&marker = 0x7ffcdb861384` (`marker = 0`)
  * `walk_stack(1, 3)` frame: `&marker = 0x7ffcdb861354` (`marker = 10`) — shifted by `-0x30` bytes
  * `walk_stack(2, 3)` frame: `&marker = 0x7ffcdb861324` (`marker = 20`) — shifted by `-0x30` bytes
  * `walk_stack(3, 3)` frame: `&marker = 0x7ffcdb8612f4` (`marker = 30`) — shifted by `-0x30` bytes
* **Stack Frame Reuse (`dump_frame`):**
  * During `[enter] depth=0`, `dump_frame` pushes a temporary frame above `walk_stack(0)` (`&local_int = 0x7ffcdb861334`, `local_buf = 0x7ffcdb861340`).
  * When `dump_frame` returns, its frame is popped (deallocated).
  * During `[exit] depth=0`, calling `dump_frame` again reuses the exact same stack frame addresses (`0x7ffcdb861334` and `0x7ffcdb861340`).

### Variable Lifetimes & Pointer Aliasing
* **`marker` (in `walk_stack`):** Automatic storage duration. Each recursive invocation owns its own distinct `marker` instance on the stack. Its lifetime begins when entering `walk_stack` and ends only when that specific recursive depth returns (after all deeper recursive calls unwind).
* **`local_int` and `local_buf` (in `dump_frame`):** Automatic storage duration. Created upon entering `dump_frame` and destroyed immediately upon reaching the closing brace `}` of `dump_frame`.
* **Pointer Aliasing (`p_local` -> `local_int`):** Inside `dump_frame`, `int *p_local = &local_int;` creates a local pointer aliasing `local_int` (both share the exact same address, e.g., `0x7ffcdb861334` at `depth=0`). Because `p_local` points to a stack-allocated variable, its target becomes invalid as soon as `dump_frame` returns. No `free()` is ever needed or allowed on `p_local`.


## 2. `aliasing_example.c`

### Execution Output
```text
aliasing_example: aliasing and use-after-free (Valgrind should report it)
  a=0x5e59aa651420 b=0x5e59aa651420 a[2]=22 b[2]=22
  after free(a): b=0x5e59aa651420 (dangling)
  reading b[2]=2074492350
  wrote b[3]=1234
```

### Step-by-Step Memory Map (Stack vs. Heap)
* **Stack Memory (`main` frame):**
  * Pointer `a` (`int *`): 8 bytes stored on the Stack.
  * Pointer `b` (`int *`): 8 bytes stored on the Stack.
  * Both `a` and `b` have automatic storage duration tied to `main()`, meaning the pointer variables themselves remain on the stack until `main()` returns—even after the heap memory they point to is freed.
* **Heap Memory:**
  * `malloc` dynamically allocates a single contiguous block of integers (`4 * sizeof(int)` = 16 bytes) at heap address `0x5e59aa651420`.
  * **Phase 1 (Before `free(a)`):** `a` holds `0x5e59aa651420`. Executing `b = a;` copies the address value, creating a **pointer alias**. Both `a` and `b` point to the exact same heap chunk (`a[2]` and `b[2]` both read `22` at offset `+8` bytes from `0x5e59aa651420`).
  * **Phase 2 (At `free(a)`):** Calling `free(a)` returns the 16-byte heap block at `0x5e59aa651420` back to the `glibc` allocator's free list (`tcache`). The heap lifetime of that allocation officially ends here.
  * **Phase 3 (After `free(a)` - Use-After-Free):** `free(a)` does **not** zero out the address stored in `a` or `b`. Variable `b` still holds `0x5e59aa651420`, making `b` a **dangling pointer**.
    * Reading `b[2]` triggers an **Invalid Read (Use-After-Free)** of 4 bytes at `0x5e59aa651428`: the original value `22` was overwritten by allocator metadata/garbage, producing `2074492350`.
    * Writing `b[3] = 1234` triggers an **Invalid Write (Use-After-Free)** of 4 bytes at `0x5e59aa65142c`, silently corrupting freed heap memory without triggering an immediate segmentation fault.

### Variable Lifetimes & Ownership Rules
* **Ownership:** `a` is the original owner returned by `malloc`, while `b` is a non-owning alias. Because `free(a)` already released `0x5e59aa651420`, calling `free(b)` afterward would cause a fatal **Double Free** corruption.
* **Lifetime Mismatch:** The heap buffer's lifetime ended at `free(a)`, whereas the stack pointer `b` outlived its target, causing undefined behavior upon dereference.

---

## 3. Critical AI Review (Correction of AI Output)

### Initial AI Explanation / Assumption
> During the initial static code review of `stack_example.c` (before running the binary), the AI stated: *"When `walk_stack(1)` calls `dump_frame("enter", 1)`, this new execution of `dump_frame` takes the exact free space left right above `walk_stack(1)` (reusing the previous `dump_frame` address)."*

### Why It Was Incomplete / Misleading
* The phrasing implied that consecutive calls to `dump_frame` across different recursive depths (`depth=0` vs. `depth=1`) reuse the exact same memory addresses.
* Inspecting the actual runtime addresses proved this false:
  * At `[enter] depth=0`, `dump_frame` placed `local_int` at `0x7ffcdb861334`.
  * At `[enter] depth=1`, `walk_stack(1)` pushed its own `0x30`-byte stack frame onto the stack **before** calling `dump_frame`, shifting `dump_frame`'s `local_int` down by `-0x30` bytes to `0x7ffcdb861304`.
* Additionally, in `aliasing_example.c`, a naive assumption would be that reading `b[2]` after `free(a)` still prints `22` or immediately crashes; in reality, `glibc` overwrites freed chunk bytes with allocator metadata (`2074492350`), demonstrating silent memory corruption rather than an immediate segfault.

### Corrected Explanation
* In `stack_example.c`, `dump_frame` does **not** reuse addresses across different recursion depths because each active `walk_stack` frame remains locked on the stack until its children return. Exact stack address reuse (`0x7ffcdb861334`) occurs strictly between `[enter]` and `[exit]` calls **at the exact same recursion depth**, once all deeper frames have unwound.


## Summary of Findings (`stack_example.c` & `aliasing_example.c`)

* **`stack_example.c` (Healthy Automatic Stack Management):**
  * **Memory Region:** 100% Stack (0 bytes allocated on the Heap).
  * **Behavior:** Each recursive call to `walk_stack` pushes a distinct 48-byte (`0x30`) stack frame at lower memory addresses. Local variables (`marker`, `local_int`, `local_buf`, and the local alias `p_local`) have strictly automatic lifetimes bound to their enclosing function block and are cleanly popped upon return.
  * **Verdict:** No memory leaks, no invalid accesses, and no manual `free()` required.

* **`aliasing_example.c` (Pointer Aliasing & Use-After-Free Bug):**
  * **Memory Regions:** Stack pointers `a` and `b` both point to the same 16-byte Heap block (`0x5e59aa651420`) created by `malloc`.
  * **Root Cause:** Assigning `b = a` copies the memory address (creating an alias) rather than duplicating the heap data. Calling `free(a)` ends the lifetime of the heap allocation, but leaves `b` holding the stale address (`0x5e59aa651420`), turning `b` into a **dangling pointer**.
  * **Consequence (Undefined Behavior):** Dereferencing `b` after `free(a)` triggers a **Use-After-Free**: reading `b[2]` returns allocator metadata/garbage (`2074492350` instead of `22`), and writing `b[3] = 1234` silently corrupts freed heap memory.
