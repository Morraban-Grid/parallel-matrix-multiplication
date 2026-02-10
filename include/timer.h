#ifndef TIMER_H
#define TIMER_H

/**
 * @file timer.h
 * @brief Execution time measurement utilities for benchmarking.
 *
 * Provides a simple function to obtain the current time in seconds
 * with microsecond precision. Used for consistent benchmarking
 * across all implementations of the project.
 *
 * @project Parallel Matrix Multiplication
 */

#include <sys/time.h>

/**
 * @brief Returns the current time in seconds.
 *
 * Uses gettimeofday to obtain wall-clock time with microsecond precision.
 *
 * @return Current time in seconds as a double.
 */
static inline double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}

#endif /* TIMER_H */
