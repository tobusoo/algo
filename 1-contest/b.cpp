#include <iostream>
#include <vector>

int bin_search(std::vector<int>& v, int value)
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

    int left_d = value - v[l];
    int right_d = v[r] - value;
    return left_d <= right_d ? v[l] : v[r];
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
        int value = bin_search(v, i);
        printf("%d\n", value);
    }

    return 0;
}