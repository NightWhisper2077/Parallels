#include <iostream>
#include <vector>
#include <math.h>
#define COUNT 10000000
using namespace std;

int main() {
    vector<TYPE> sins;
    TYPE val, sum = 0;

    for (int i = 0; i < COUNT; i++) {
        val = sinf(((TYPE)(2 * i * M_PI))/COUNT);

        sins.push_back(val);

        sum += val;
    }

    return 0;
}
