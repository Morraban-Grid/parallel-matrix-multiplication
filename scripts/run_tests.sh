#!/usr/bin/env bash

# Execution and benchmarking script
# Project: Parallel Matrix Multiplication

echo "======================================"
echo " Parallel Matrix Multiplication Tests "
echo "======================================"

echo ""
echo ">> Building implementations..."

# Build all versions
./scripts/build_openmp.sh
./scripts/build_mpi.sh
./scripts/build_cuda.sh

echo ""
echo ">> Running sequential version..."
time ./multimat_seq_opt 2>&1 | grep real

echo ""
echo ">> Running OpenMP version (OMP_NUM_THREADS=4)..."
export OMP_NUM_THREADS=4
time ./multimat_openmp 2>&1 | grep real

echo ""
echo ">> Running Pthreads version..."
time ./multimat_pthreads 2>&1 | grep real

echo ""
echo ">> Running MPI version (4 processes)..."
time mpirun -np 4 ./multimat_mpi 2>&1 | grep real

echo ""
echo ">> Running CUDA version..."
time ./multimat_cuda 2>&1 | grep real

echo ""
echo "======================================"
echo " End of tests"
echo "======================================"
