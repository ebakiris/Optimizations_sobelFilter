# Optimizations_sobelFilter
## This project made by Bakiris Emmanouil during the course High Performance Computing Systems of University of Thessaly during the academic year 2018-2019.

The main purpose of this project is to experiment with different kinds of optimizations in the sobel filter.
The optimizations that have been used are Loop Interchange, Loop unrolling, Loop fusion, Function Inlining, Loop Invariant code motion,
Common Subexpression Elimination and Strength Reduction. First of all, it is used the icc compile and the code is in C language.There are two subdirectories using two kinds of flags(-fast and -O0).The experiments took place in machine described in specs file.Especially, there are 8 files in each subdirectory that show each step every time using an additional kind of optimization.There are makefiles that describe how to run and experiment .
