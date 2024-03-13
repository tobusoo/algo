#include <iostream>
#include <vector>

bool is_possible(std::vector<size_t>& pref_sum, size_t min_max, size_t k)
{
    size_t cows = 1;
    size_t last_cow = 0;
    size_t n = pref_sum.size();

    for (size_t i = 0; i < n; i++) {
        if (pref_sum[i] - last_cow >= min_max) {
            cows++;
            last_cow = pref_sum[i];
        }
    }

    return cows >= k;
}

int main()
{
    size_t n, k;
    std::cin >> n >> k;

    std::vector<size_t> pref_sub_sum(n - 1, 0);
    size_t num, num2;
    std::cin >> num >> num2;
    pref_sub_sum[0] = num2 - num;
    size_t max_dist = num2 - num;

    for (size_t i = 1; i < n - 1; i++) {
        std::cin >> num;
        pref_sub_sum[i] = pref_sub_sum[i - 1] + num - num2;
        max_dist = std::max(max_dist, pref_sub_sum[i]);
        num2 = num;
    }

    size_t l = 0;
    size_t r = max_dist + 1;
    size_t mid;
    while (r - l > 1) {
        mid = (r + l) / 2;
        if (is_possible(pref_sub_sum, mid, k))
            l = mid;
        else
            r = mid;
    }

    std::cout << l << '\n';

    return 0;
}