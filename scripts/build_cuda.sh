#!/bin/bash

SRC="src/cuda/multimat_cuda_opt.cu"
OUT="multimat_cuda"

echo "Compiling CUDA version..."

nvcc -O2 "$SRC" -o "$OUT"

if [ $? -eq 0 ]; then
    echo "CUDA compilation successful."
    echo "Executable generated: $OUT"
else
    echo "CUDA compilation failed."
    exit 1
fi
