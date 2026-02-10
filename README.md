# Parallel Matrix Multiplication

High-performance implementations of square matrix multiplication using multiple parallel programming models:

- Sequential (cache blocking)
- OpenMP
- POSIX Threads (pthreads)
- MPI (Message Passing Interface)
- CUDA (GPU)

This project is designed to study, benchmark, and compare different parallelization strategies applied to the same computational problem.

---

## 📌 Objective

To evaluate the performance impact of different parallel programming paradigms on matrix multiplication while keeping the algorithmic logic consistent across implementations.

The project also serves as a benchmarking and educational framework for:

- CPU parallelism
- Distributed memory parallelism
- GPU acceleration
- Cache optimization techniques

---

## 🗂️ Project Structure

parallel-matrix-multiplication/
├── src/
│ ├── secuencial/
│ ├── openmp/
│ ├── pthreads/
│ ├── mpi/
│ └── cuda/
│
├── include/
├── scripts/
├── results/
└── README.md


---

## 🧠 Implementations

| Version     | Technique                    | File                                  |
|--------------|------------------------------|----------------------------------------|
| Sequential   | Cache blocking               | `src/secuencial/multimat_seq_opt.c`  |
| OpenMP       | Shared-memory parallelism    | `src/openmp/multimat_openmp_opt.c`   |
| Pthreads     | Manual threading             | `src/pthreads/multimat_pthreads_opt.c`|
| MPI          | Distributed processes        | `src/mpi/multimat_mpi_opt.c`         |
| CUDA         | GPU parallelization          | `src/cuda/multimat_cuda_opt.cu`      |

All implementations multiply two **500×500** matrices where:

- **A** is the identity matrix
- **B** contains row-dependent values
- The result **C** must equal **B** (validation rule)

---

## ⚙️ Requirements

- GCC with OpenMP support
- MPICC (MPI)
- NVIDIA CUDA Toolkit
- Linux environment (tested on Ubuntu)

---

## 🛠️ Build

Make scripts executable (only once):

```bash
chmod +x scripts/*.sh

Compile each version:

./scripts/build_openmp.sh
./scripts/build_mpi.sh
./scripts/build_cuda.sh

▶️ Run Tests and Benchmark
./scripts/run_tests.sh
This script:

Compiles all implementations
Runs them sequentially
Displays execution time for comparison

📊 Benchmark Results

Execution times can be stored in the results/ directory for later analysis.
These files are intentionally ignored by Git.

🔐 Notes on Repository Hygiene

This repository is configured to:

Avoid committing binaries

Avoid committing credentials

Avoid committing benchmark results

Maintain a clean and professional Git history

🎓 Educational Purpose

This project is intended for learning and analyzing:

Parallel programming models

Performance comparison

Memory hierarchy effects

GPU vs CPU computation

Distributed vs shared memory paradigms