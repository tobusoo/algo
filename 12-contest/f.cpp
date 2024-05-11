#include <iostream>

using ull = unsigned long long;
ull mod;

ull modular_pow(ull x, ull pow)
{
    if (pow == 0)
        return 1;
    ull val = modular_pow(x % mod, pow / 2) % mod;
    if (pow % 2 == 0)
        return (val * val) % mod;

    return ((x % mod) * ((val * val) % mod)) % mod;
}

int main()
{
    ull n, m, k;
    std::cin >> n >> m >> k >> mod;

    std::cout << ((modular_pow(m, n) % mod) * (modular_pow(k, mod - 2) % mod)) % mod << '\n';

    return 0;
}