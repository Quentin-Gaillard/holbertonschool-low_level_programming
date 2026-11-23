# Memory Maps and Lifetime Analysis

## 0. Stack vs. Heap Overview

Stack memory:
- Allocated automatically when a function is called (each call pushes a new stack frame).
- Lifetime is tied strictly to the function block. When the function returns, its stack frame is popped and all local variables inside it are destroyed.
- Never freed manually with free(). Any pointer pointing to a stack variable becomes a dangling pointer as soon as that function returns.

Heap memory:
- Allocated dynamically using malloc, calloc, or realloc.
- Lifetime persists across function calls and returns until free() is explicitly called.
- Must have one clear owner responsible for calling free() once. Copying a pointer (b = a) creates an alias sharing the same address; calling free(a) immediately invalidates b.

---

## 1. stack_example.c

Program behavior and memory layout:
This program uses 0 bytes of heap memory. Every variable lives on the stack and has automatic storage duration.

On this x86_64 machine, the stack grows downward toward lower memory addresses. Each recursive call to walk_stack(depth, 3) allocates a new 48-byte (0x30) stack frame:
- depth=0: &marker = 0x7ffcdb861384 (marker = 0)
- depth=1: &marker = 0x7ffcdb861354 (marker = 10)
- depth=2: &marker = 0x7ffcdb861324 (marker = 20)
- depth=3: &marker = 0x7ffcdb8612f4 (marker = 30)

Each recursive call owns its own separate copy of marker. Its lifetime begins when entering walk_stack at that depth and ends only when all deeper calls return and that specific frame unwinds.

Stack frame reuse in dump_frame:
- At [enter] depth=0, dump_frame pushes a temporary frame above walk_stack(0) with &local_int = 0x7ffcdb861334 and local_buf = 0x7ffcdb861340.
- When dump_frame returns, its stack frame is popped.
- At [exit] depth=0, dump_frame is called again and reuses the exact same addresses (0x7ffcdb861334 and 0x7ffcdb861340).

Pointer aliasing and lifetimes:
Inside dump_frame, p_local is initialized with &local_int, so both share the exact same stack address (for example, 0x7ffcdb861334 at depth=0). Because p_local points to a local stack variable, both local_int and p_local become invalid the moment dump_frame returns.

---

## 2. aliasing_example.c

Program behavior and memory layout:
- Stack variables: pointers a and b live inside main's stack frame and remain on the stack until main returns.
- Heap allocation: malloc allocates a contiguous block of integers at heap address 0x5e59aa651420.

Step-by-step execution:
1. Initial state: a points to 0x5e59aa651420. Executing b = a copies the address, creating a pointer alias. Both a and b point to the exact same heap memory and read 22 at index 2.
2. Deallocation: Calling free(a) releases the heap block at 0x5e59aa651420 back to the allocator. The lifetime of the heap data ends at this line.
3. Dangling pointer and Use-After-Free: free(a) does not clear the address stored in b. Variable b still holds 0x5e59aa651420, turning b into a dangling pointer.
- Reading b triggers a Use-After-Free read: the original value 22 was already overwritten by allocator metadata, printing garbage (2074492350).
- Writing b = 1234 triggers a Use-After-Free write, silently corrupting freed heap memory.

Ownership rules:
a is the owner returned by malloc, while b is a non-owning alias. Calling free(b) after free(a) would cause a double-free error.

---

## 3. Critical AI Review

Initial AI assumption:
Before running stack_example, the AI suggested that calling dump_frame at depth=1 would reuse the exact stack address left free by dump_frame at depth=0.

Why it was wrong:
Checking the actual runtime addresses showed that walk_stack(1) pushes its own 0x30-byte frame onto the stack before calling dump_frame, which shifts dump_frame's local_int down from 0x7ffcdb861334 to 0x7ffcdb861304.

Corrected explanation:
dump_frame does not reuse addresses across different recursive depths because active walk_stack frames stay on the stack until their children finish. Exact stack address reuse only happens between [enter] and [exit] calls at the exact same recursion depth.

---

## Summary

- stack_example.c uses only the stack, manages lifetimes automatically as frames push and pop, and has no memory bugs.
- aliasing_example.c demonstrates how pointer aliasing creates a dangling pointer when the owner calls free(a), leading to Use-After-Free reads and writes through alias b.
