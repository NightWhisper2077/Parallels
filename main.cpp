#include <iostream>
#include <vector>
#include <cmath>
#define COUNT 10000000
using namespace std;

int main() {
    vector<TYPE> sins;
    TYPE val, sum = 0;
    cout.precision(17);
    for (int i = 0; i < COUNT; i++) {
        val = sin((2 * i * M_PI) / COUNT);
        sum += val;

        sins.push_back((TYPE)val);
    }

    cout << "Summary of array: " << sum;
    return 0;
}
