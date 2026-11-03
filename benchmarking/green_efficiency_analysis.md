
# Measurement Methodology


## Baseline Diagnostics

The first measurement phase established a control baseline using the "baseline_loop.c" program provided by Holberton (my beloved school). This program ran a script executing 100 million iterations of a modulo operation on a volatile variable. We needed this baseline to separate system background noise and slowdowns from the actual performance of our algorithm. This allowed us to measure the background OS impact before modifying any code (see text file .md, on my github account).

## Algorithmic Comparison

The second step compared two different ways to code the same problem: counting even numbers in a 50,000-element array. The first approach used simple nested loops (rightly called "naive"), while the second relied on an optimized, single-pass linear traversal. Keeping the same hardware (and the same programs open), I clearly saw that the second code was much more efficient with system resources (see text file).
For this final diagnostic level (the instruments), I precisely timed each data processing step in instrumentation_lab.c. I placed measurement checkpoints around three successive blocks: data generation (BUILD_DATA), calculations (PROCESS), and checksum verification (REDUCE). This breakdown let me target exactly which logic block consumed the most CPU cycles. (With my high-end processor, it turns out I hit 0.0000000 sec across all 4 steps).

## Observed Performance Differences

The results show massive performance gaps from one model to another. At rest, the system runs between 0.058 and 0.061 seconds. As soon as a heavy background load is introduced (running Helldivers 2 and Total War: Warhammer 3 at the same time, just to compare and fun), this time jumps to between 0.065 and 0.068 seconds due to CPU context switching.
But the most obvious difference appears when traversing the array. The naive approach, stuck in O(N²) time complexity because of its nested loops, takes an average of 0.482 seconds to process the 50,000 integers. With my high-end processor, all measurements came back as 0.0000000 seconds. In order to establish a performance ratio, I retained a value of 0.000001 seconds for the optimized algorithm (making it at least 482,000 times faster than the naive version).



## Relation Between Runtime and Energy Consumption

A software's runtime translates directly into power consumption and heat. When an inefficient algorithm—like our O(N²) nested loop—forces the processor to run 1.25 billion useless modulo operations instead of the required 50,000, it keeps the CPU core at peak power for much longer. The operating system monopolizes a thread and drains power continuously. This prolonged execution prevents the processor from dropping into its energy-saving idle modes (C-states). Cleaning up the code and removing these redundant calculations directly cuts down on kilowatt-hour consumption, and by extension, the hardware's carbon footprint.

## Limitations of the Experiment

The current test setup faces two critical engineering constraints:
The standard C89 clock() function within the Windows UCRT64 abstraction layer lacks precision. It was completely unable to capture the sub-millisecond runtime of the single-pass algorithm without artificially multiplying the workload loops by a factor of 1,000.
Running these benchmarks on a general-purpose, multitasking operating system introduces external interference from background processes, which prevents us from isolating the raw code performance 100%.

## Practical Engineering Takeaway

As a software engineer, true optimization relies on architectural efficiency rather than raw hardware power. Micro-optimizations or relying on modern multi-core CPUs cannot fix a poorly designed time complexity model. Writing code with linear structures and minimal nesting must remain a primary goal from the very start of development to build sustainable, high-performance software systems.
