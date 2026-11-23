# Crash Report: crash_example.c

## 1. Crash Description

When running ./crash_example, the program prints its first two lines ("crash_example: deterministic NULL dereference (segmentation fault)" and "requesting n=0") and then immediately terminates with a Segmentation fault (signal SIGSEGV).

---

## 2. Root Cause and Causal Chain

Memory regions involved:
- Stack memory: local variables int *nums and int n inside main(), plus parameter int n inside allocate_numbers().
- Heap memory: 0 bytes allocated (malloc is never reached).
- Invalid virtual address: 0x0 (NULL), a protected unmapped memory page managed by the OS kernel.

Step-by-step causal chain from code to crash:
1. In main (line 23), n is set to 0 and nums is set to NULL on the stack.
2. In main (line 28), allocate_numbers(n) is called with n = 0.
3. Inside allocate_numbers (lines 9-10), the guard condition if (n <= 0) is true, so the function returns NULL (0x0) right away without calling malloc.
4. Back in main (line 28), nums receives NULL (0x0).
5. In main (line 30), the program executes nums = 42 without checking if nums is NULL. In C, nums means *(nums + 0), which tries to write 4 bytes at virtual address 0x0.
6. Because address 0x0 is intentionally unmapped and non-writable in user space, the CPU triggers a page fault and the Linux kernel kills the process with SIGSEGV.

Category of Undefined Behavior:
- NULL pointer dereference (writing to address 0x0 through a NULL pointer).

---

## 3. Critical AI Review

Initial AI suggestions:
When asked why a C program crashes right after calling an allocation function, an AI usually lists three generic possibilities: malloc ran out of memory, there is a heap buffer overflow, or a NULL return value was not checked.

Evaluation of those suggestions:
- Incorrect for this case: Claiming that malloc failed due to low memory or that there is a buffer overflow on the heap is wrong here. malloc on line 12 is never even executed because n is hardcoded to 0 in main, so zero bytes are allocated on the heap.
- Correct: Pointing out the missing NULL check in main after calling allocate_numbers(n) accurately explains why the program crashes deterministically on every single run.

---

## 4. Suggested Fix (Optional)

In main (right after line 28), add a check: if (nums == NULL) return (1); before trying to write to nums.

---

## Summary

This program crashes not because the computer ran out of memory, but because main() blindly assumes allocate_numbers() always returns a valid heap pointer. Since n is 0, allocate_numbers() hits its safety check (if (n <= 0)) and returns NULL, which stores address 0x0 in nums on the stack. Writing nums = 42 then tries to access protected memory at address 0x0, causing an immediate segmentation fault. The main lesson is simple: never dereference a pointer returned by a helper function or malloc without checking if it is NULL first.


VOUALA