#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;
    std::vector<int> v(n, 0);
    std::vector<int> d(n + 1, 0);
    int temp;

    for (size_t i = 0; i < n; i++) {
        std::cin >> temp;
        v[i] = temp;
    }

    d[1] = v[0];
    for (size_t i = 2; i <= n; i++) {
        d[i] = std::min(d[i - 1] + v[i - 1], d[i - 2] + v[i - 1]);
    }

    // for (auto&& i : d) {
    //     std::cout << i << ' ';
    // }
    // std::cout << '\n';

    std::cout << d.back() << '\n';
    return 0;
}