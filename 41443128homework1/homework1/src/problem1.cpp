#include <iostream>

using namespace std;

long long ackermannRecursive(long long m, long long n) {
    if (m < 0 || n < 0) {
        throw "m or n < 0";
    }

    if (m == 0) {
        return n + 1;
    }

    if (n == 0) {
        return ackermannRecursive(m - 1, 1);
    }

    return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
}

long long ackermannNonRecursive(long long m, long long n) {
    if (m < 0 || n < 0) {
        throw "m or n < 0";
    }

    const int STACK_SIZE = 1000000;
    long long* data = new long long[STACK_SIZE];
    int top = 0;

    data[top++] = m;

    while (top > 0) {
        m = data[--top];

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            n = 1;

            if (top >= STACK_SIZE) {
                delete[] data;
                throw "stack overflow";
            }

            data[top++] = m - 1;
        } else {
            if (top + 2 > STACK_SIZE) {
                delete[] data;
                throw "stack overflow";
            }

            data[top++] = m - 1;
            data[top++] = m;
            n = n - 1;
        }
    }

    delete[] data;
    return n;
}

int main() {
    long long m = 2;
    long long n = 3;

    cout << "Recursive: "
         << ackermannRecursive(m, n) << '\n';

    cout << "Non-recursive: "
         << ackermannNonRecursive(m, n) << '\n';

    return 0;
}
