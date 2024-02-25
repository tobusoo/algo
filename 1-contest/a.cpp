#include <iostream>
#include <vector>

bool bin_search(std::vector<int>& v, int value)
{
    int l = 0;
    int r = v.size() - 1;
    int mid = 0;
    while (r - l > 1) {
        mid = (r + l) / 2;
        if (v[mid] >= value)
            r = mid;
        else
            l = mid;
    }

    return v[l] == value;
}

int main()
{
    size_t n, k;
    std::cin >> n >> k;
    std::vector<int> v, v2;
    for (size_t i = 0; i < n; ++i) {
        int temp;
        std::cin >> temp;
        v.push_back(temp);
    }
    for (size_t i = 0; i < k; ++i) {
        int temp;
        std::cin >> temp;
        v2.push_back(temp);
    }

    for (auto&& i : v2) {
        if (bin_search(v, i))
            std::cout << "YES\n";
        else
            std::cout << "NO\n";
    }

    return 0;
}