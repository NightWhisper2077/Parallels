#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#include <time.h>
#define COUNT 8
#define SIZE 20000

void matrix_vector_product(double *a, double *b, double *c, int m, int n)
{
    for (int i = 0; i < m; i++) {
        c[i] = 0.0;
        for (int j = 0; j < n; j++)
            c[i] += a[i * n + j] * b[j];

    }
}

void matrix_vector_product_omp(double *a, double *b, double *c, int m, int n)
{
#pragma omp parallel num_threads(COUNT)
    {
        int nthreads = omp_get_num_threads();
        int threadid = omp_get_thread_num();

        int items_per_thread = m / nthreads;
        int items_per_thread_mod = m % nthreads;
        int lb = threadid * items_per_thread + (items_per_thread_mod > threadid? threadid: items_per_thread_mod);
        int ub = (threadid + 1) * items_per_thread + (items_per_thread_mod > threadid? threadid + 1: items_per_thread_mod) - 1;

        for (int i = lb; i <= ub; i++) {
            c[i] = 0.0;
            for (int j = 0; j < n; j++)
                c[i] += a[i * n + j] * b[j];
        }
    }
}

void run_serial(int m, int n)
{
    double* a = (double*)malloc(sizeof(double) * m * n);
    double* b = (double*)malloc(sizeof(double) * n);
    double* c = (double*)malloc(sizeof(double) * m * n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            a[i * n + j] = i + j;
        c[i] = 0.0;
    }
    for (int j = 0; j < n; j++) {
        b[j] = j;
    }

    double t = omp_get_wtime();

    matrix_vector_product(a, b, c, m, n);

    double t1 = omp_get_wtime();

    printf("%.6f", t1-t);
}

void run_parallel(int m, int n)
{
    double *a, *b, *c;
    a = (double*)malloc(sizeof(*a) * m * n);
    b = (double*)malloc(sizeof(*b) * n);
    c = (double*)malloc(sizeof(*c) * m);
#pragma omp parallel num_threads(COUNT)
    {
        int nthreads = omp_get_num_threads();
        int threadid = omp_get_thread_num();
        int items_per_thread = m / nthreads;
        int items_per_thread_mod = m % nthreads;

        int lb = threadid * items_per_thread + (items_per_thread_mod > threadid? threadid: items_per_thread_mod);
        int ub = (threadid + 1) * items_per_thread + (items_per_thread_mod > threadid? threadid + 1: items_per_thread_mod) - 1;

        for (int i = lb; i <= ub; i++) {
            for (int j = 0; j < n; j++)
                a[i * n + j] = i + j;
            c[i] = 0.0;
        }
    }
    for (int j = 0; j < n; j++)
        b[j] = j;

    double t = omp_get_wtime();

    matrix_vector_product_omp(a, b, c, m, n);

    double t1 = omp_get_wtime();

    printf("%.6f", t1-t);
}

int main()
{
    run_serial(SIZE, SIZE);
}