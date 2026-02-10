#!/usr/bin/env bash

# Source file for the optimized OpenMP matrix multiplication implementation
SRC="src/openmp/multimat_openmp_opt.c"

# Output executable name
OUT="multimat_openmp"

# Inform the user about the compilation step
echo "Compiling OpenMP version..."

# Compile the OpenMP program with optimization level O2 and OpenMP support
gcc -O2 -fopenmp "$SRC" -o "$OUT"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "OpenMP compilation successful."
    echo "Generated executable: $OUT"
else
    echo "OpenMP compilation failed."
    exit 1
fi
