#include <iostream>

using ull = unsigned long long;
ull mod = 1e9 + 7;

ull factorial(ull n)
{
    if (n <= 1)
        return 1;
    ull ans = 1;
    for (ull i = 1; i <= n; i++)
        ans = (ans * i) % mod;

    return ans;
}

ull modular_pow(ull x, ull pow)
{
    if (pow == 0)
        return 1;
    ull val = modular_pow(x % mod, pow / 2) % mod;
    if (pow % 2 == 0)
        return (val * val) % mod;

    return ((x % mod) * ((val * val) % mod)) % mod;
}

ull bin_coef(ull n, ull k)
{
    ull a = factorial(n);
    ull b = factorial(k) * factorial(n - k);

    return ((a % mod) * (modular_pow(b, mod - 2) % mod)) % mod;
}

int main()
{
    ull n, k;
    std::cin >> n >> k;
    std::cout << bin_coef(n, k) << '\n';

    return 0;
}