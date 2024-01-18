# Optimizations_sobelFilter

Gained :

-Step-by-step sequential optimization on CPU.
-Familiarity with basic principles of experimentation and measurement in computer systems.
-Familiarity with compiler and optimizations.

The main purpose of this project is to experiment with different kinds of optimizations in the sobel filter.
The optimizations that have been used are Loop Interchange, Loop unrolling, Loop fusion, Function Inlining, Loop Invariant code motion,
Common Subexpression Elimination and Strength Reduction. First of all, it is used the icc compile and the code is in C language.There are two subdirectories using two kinds of flags(-fast and -O0).The experiments took place in machine described in specs file.Especially, there are 8 files in each subdirectory that show each step every time using an additional kind of optimization.There are makefiles that describe how to run and experiment .
