#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;

    std::vector<size_t> v;
    std::vector<size_t> prefix_sum = {0};
    std::vector<size_t> prefix_xor = {0};
    size_t temp;

    for (size_t i = 0; i < n; i++) {
        std::cin >> temp;
        v.push_back(temp);
    }

    prefix_sum.push_back(v[0]);
    prefix_xor.push_back(v[0]);
    for (size_t i = 1; i < n; i++) {
        prefix_sum.push_back(prefix_sum[i] + v[i]);
        prefix_xor.push_back(prefix_xor[i] ^ v[i]);
    }

    size_t q;
    std::cin >> q;
    size_t l, r, act;

    for (size_t i = 0; i < q; i++) {
        std::cin >> act >> l >> r;
        if (act == 1)
            std::cout << (prefix_sum[r] - prefix_sum[l - 1]) << '\n';
        else
            std::cout << (prefix_xor[r] ^ prefix_xor[l - 1]) << '\n';
    }

    return 0;
}