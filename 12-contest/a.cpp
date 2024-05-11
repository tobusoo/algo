#include <iostream>
#include <numeric>

using ull = unsigned long long;
int main()
{
    ull n, k;
    std::cin >> n >> k;
    std::cout << n * k / std::gcd(n, k) << '\n';
    return 0;
}