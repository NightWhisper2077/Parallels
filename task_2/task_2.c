#include <stdio.h>
#include <math.h>
#include <omp.h>

const double PI = 3.14159265358979323846;

double func (double x) {
    return exp(-x * x);
}

double integrate(double (*func)(double), double a, double b, double n) {
    double h = (b - a)/n;
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        sum += func(a + h * (i + 0.5));
    }

    sum *= h;

    return sum;
}

double integrate_omp(double (*func)(double), double a, double b, double n) {
    double h = (b - a)/n;
    double sum = 0.0;

#pragma omp parallel num_threads(COUNT)
    {
        printf("%d\n", omp_get_thread_num());
        int nthreads = omp_get_num_threads();
        int threadid = omp_get_thread_num();
        int items_per_thread = n / nthreads;
        int items_per_thread_mod = (int)n % nthreads;
        int lb = threadid * items_per_thread + (items_per_thread_mod > threadid? threadid: items_per_thread_mod);
        int ub = (threadid + 1) * items_per_thread + (items_per_thread_mod > threadid? threadid + 1: items_per_thread_mod) - 1;

        double sumloc = 0.0;
        for (int i = lb; i <= ub; i++)
        {
            sumloc += func(a + h * (i + 0.5));
        }
#pragma omp atomic
        sum += sumloc;
    };

    sum *=h;

    return sum;
}

double run_serial(double a, double b, double nsteps)
{
    double t = omp_get_wtime();
    double res = integrate(func, a, b, nsteps);
    double t1 = omp_get_wtime();
    return t1 - t;
}
double run_parallel(double a, double b, double nsteps)
{
    double t = omp_get_wtime();
    double res = integrate_omp(func, a, b, nsteps);
    double t1 = omp_get_wtime();
    return t1 - t;
}

int main()
{
    double a = -4;
    double b = 4;
    double nsteps = 40000000;

    double res_serial = run_serial(a, b, nsteps);
    double res_parallel = run_parallel(a, b, nsteps);

    printf("serial time - %.6f, parallel time - %.6f, diff - %.6f", res_serial, res_parallel, res_serial/res_parallel);
}