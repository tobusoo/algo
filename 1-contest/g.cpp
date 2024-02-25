#include <algorithm>
#include <iostream>
#include <vector>

size_t qsort(std::vector<int>& a, int left, int right)
{
    size_t permut = 0;
    if (right <= left)
        return 0;
    int q = a[(left + right) / 2];
    int i = left;
    int j = right;
    while (i <= j) {
        while (a[i] < q) {
            ++i;
            permut++;
        }
        while (q < a[j]) {
            --j;
            permut++;
        }
        if (i <= j) {
            std::swap(a[i], a[j]);
            ++i;
            --j;
        }
    }

    permut += qsort(a, left, j);
    permut += qsort(a, i, right);

    return permut;
}

int main()
{
    size_t n = 0;
    std::cin >> n;
    std::vector<int> v;
    for (size_t i = 1; i <= n; i++) {
        v.push_back(i);
    }

    // std::vector<int> temp = v;
    // std::vector<int> res = v;
    // size_t max_permut = 0;
    // size_t permut = 0;
    // do {
    //     temp = v;
    //     permut = qsort(temp, 0, temp.size());
    //     for (auto&& i : v) {
    //         std::cout << i << ' ';
    //     }
    //     std::cout << "permut: " << permut << '\n';
    //     if (permut > max_permut) {
    //         max_permut = permut;
    //         res = v;
    //     }
    // } while (std::next_permutation(v.begin(), v.end()));
    // for (auto&& i : res) {
    //     std::cout << i << ' ';
    // }
    for (size_t i = 0; i < n; i++) {
        std::swap(v[i], v[i / 2]);
    }
    for (auto&& i : v) {
        std::cout << i << ' ';
    }

    std::cout << '\n';
    return 0;
}