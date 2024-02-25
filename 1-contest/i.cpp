#include <iostream>
#include <vector>

int buble(std::vector<int> v)
{
    size_t i;
    for (i = 0; i < v.size(); i++) {
        bool had_swap = false;
        for (size_t j = 0; j < v.size() - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                had_swap = true;
            }
        }
        if (!had_swap)
            break;
    }

    return i + 1;
}

void test(std::vector<int>& v, std::vector<int>& res, int temp, int i)
{
    v[temp - 1] = 1;
    res[i + 1] = buble(v);
}

int main()
{
    size_t n = 0;
    std::cin >> n;
    std::vector<int> v(n, 0);
    std::vector<int> res(n + 1, 0);

    res[0] = 1;
    size_t min = 0;
    size_t max = n;
    for (size_t i = 0; i < n - 1; i++) {
        int temp;
        std::cin >> temp;
        v[temp - 1] = 1;
        // test(v, res, temp, i);
        for (size_t i = 0; i < max; i++) {
            if (v[i] == 0) {
            }
        }
    }
    res[n] = 1;
    for (auto&& i : res) {
        std::cout << i << ' ';
    }

    std::cout << '\n';

    return 0;
}