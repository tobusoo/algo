#include <iostream>

using ull = unsigned long long;

ull fact(ull n)
{
    ull m = 0, f = 1;
    for (ull i = 1; i <= n; i++) {
        ull j = i;
        while (j % 2 == 0 && j > 1) {
            j /= 2;
            m++;
        }
        while (j % 5 == 0 && j > 1) {
            j /= 5;
            m--;
        }
        f = (f * j) % 10;
    }
    f = (f << m) % 10;
    return f;
}

int main()
{
    ull n;
    std::cin >> n;
    std::cout << fact(n) << '\n';
    return 0;
}