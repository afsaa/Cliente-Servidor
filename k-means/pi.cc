#include "timer.hh"
#include <iostream>
#include <omp.h>

#define NUM_THREADS 2
// g++ -std=c++11 -fopenmp -o pi pi.cc
// ./pi

using namespace std;

double parpi(size_t rectangles = 100000) {

  // This variable is shared among all the threads without any control. That's
  // fine becasue all the threads access specific parts of the array.
  double sum[NUM_THREADS];
  double width = 1.0 / (double)rectangles;

  // Ask the operating system for the desired number of threads
  omp_set_num_threads(NUM_THREADS);
  int numberOfActualThreads = 0;

#pragma omp parallel
  { // parallel region executed by each thread

    int id = omp_get_thread_num(); // the identifier of each thread
    // Ask how many actual threads we were given by the O.S
    int nthreads = omp_get_num_threads();
    if (id == 0) {
      // Only one thread will write to this shared variable
      numberOfActualThreads = nthreads;
      // cout << "Number of actual threads: " << numberOfActualThreads << endl;
    }

    // Initialize the sum array to 0 for each thread
    sum[id] = 0.0;

    // Each thread computes the area of a bunch of rectangles.
    for (size_t i = id; i < rectangles; i = i + nthreads) {
      double mid = (i + 0.5) * width;
      double height = 4.0 / (1.0 + mid * mid);
      sum[id] += height;
    }
  }
  // At this point there is only one thread of execution so we can accumulate
  // all the results of each thread and produce the final answer.
  double pi = 0.0;
  for (size_t i = 0; i < numberOfActualThreads; i++) {
    pi += width * sum[i];
  }
  return pi;
}

int main() {
  Timer t1;
  double pil = pi();
  long long t1time = t1.elapsed();
  cout << "pi\t" << pil << "\t" << t1time << endl;

  Timer t2;
  double pil = pi();
  long long t2time = t2.elapsed();
  cout << "pi\t" << pil << "\t" << t2time << endl;
}
