#!/usr/bin/env bash

# Source file for the optimized MPI matrix multiplication implementation
SRC="src/mpi/multimat_mpi_opt.c"

# Output executable name
OUT="multimat_mpi"

# Inform the user about the compilation step
echo "Compiling MPI version..."

# Compile the MPI program with optimization level O2
mpicc -O2 "$SRC" -o "$OUT"

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "MPI compilation successful."
    echo "Generated executable: $OUT"
else
    echo "MPI compilation failed."
    exit 1
fi
