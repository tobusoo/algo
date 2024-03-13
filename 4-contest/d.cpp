#include <iostream>

size_t min_x(size_t x, size_t n)
{
    size_t ans = 0;
    for (size_t i = 1; i <= n; i++) {
        ans += std::min(x / i, n);
    }

    return ans;
}

int main()
{
    size_t n, k;
    std::cin >> n >> k;

    size_t l = 0;
    size_t r = n * n;
    size_t mid;

    while (r - l > 1) {
        mid = (l + r) / 2;
        if (min_x(mid, n) < k)
            l = mid;
        else
            r = mid;
    }

    std::cout << l + 1 << '\n';
    return 0;
}