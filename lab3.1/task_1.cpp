#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <vector>
#define COUNT 20000

using namespace std;
std::mutex mut;

double* x;
double* M;
double* res;

void define(size_t left, size_t right) {
    for (int i = left; i < right; i++) {
        x[i] = 1;
        res[i] = 0;
    }

    for (int i = left * COUNT; i < right * COUNT; i++) {
        M[i] = 5;
    }
}

void matrixMult(size_t left, size_t right) {
    int half_sum = 0;

    for (int i = left; i < right; i++) {
        half_sum += M[i] * x[i % COUNT];

        if (i % COUNT == COUNT - 1) {
            mut.lock();
            res[i / COUNT] += half_sum;
            half_sum = 0;
            mut.unlock();
        }
    }

    if ((right - 1) % COUNT == COUNT - 1) {
        mut.lock();
        res[(right - 1)/ COUNT] += half_sum;
        mut.unlock();
    }
}

int main()
{
    x = new double[COUNT];
    res = new double[COUNT];
    M = new double[COUNT*COUNT];

    for (int j = 1; j <= 40; j++) {
        int countThreads = j, left, right, items_per_thread = COUNT / countThreads, items_per_thread_mod = COUNT % countThreads;

        vector<thread> threads;

        auto start = std::chrono::steady_clock::now();
        for (int i = 0; i < countThreads; i++) {
            left = i * items_per_thread + (items_per_thread_mod > i? i: items_per_thread_mod);
            right = (i + 1) * items_per_thread + (items_per_thread_mod > i? i + 1: items_per_thread_mod);

            threads.push_back(thread(define, left, right));
        }

        for (auto &thread : threads) {
            thread.join();
        }

        threads.clear();
        items_per_thread = (COUNT * COUNT) / countThreads, items_per_thread_mod = (COUNT * COUNT) % countThreads;

        for (int i = 0; i < countThreads; i++) {
            left = i * items_per_thread + (items_per_thread_mod > i? i: items_per_thread_mod);
            right = (i + 1) * items_per_thread + (items_per_thread_mod > i? i + 1: items_per_thread_mod);
            threads.push_back(thread(matrixMult, left, right));
        }

        for (auto &thread : threads) {
            thread.join();
        }

        auto end = std::chrono::steady_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Time taken for step " << j << ": " << duration.count() << " milliseconds." << std::endl;

        threads.clear();
    }

    for (int i = 0; i < COUNT; i++) {
        cout << res[i] << ' ';
    }

    return 0;
}
