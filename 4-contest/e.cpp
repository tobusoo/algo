#include <iostream>
#include <vector>

bool is_possible(std::vector<size_t>& v, std::vector<size_t>& pref_sum, size_t min_max, size_t k)
{
    size_t count = 1;
    size_t prev_sum_inter = 0;
    size_t n = pref_sum.size();

    for (size_t i = 0; i < n; i++) {
        if (v[i] >= min_max)
            return false;
        if (pref_sum[i] - prev_sum_inter >= min_max) {
            count++;
            prev_sum_inter = pref_sum[i - 1];
        }
    }

    return count <= k;
}

int main()
{
    size_t n, k;
    std::cin >> n >> k;
    std::vector<size_t> v(n, 0);
    std::vector<size_t> pref_sum(n, 0);

    size_t temp;
    std::cin >> temp;
    v[0] = temp;
    pref_sum[0] = temp;

    for (size_t i = 1; i < n; i++) {
        std::cin >> temp;
        v[i] = temp;
        pref_sum[i] = pref_sum[i - 1] + temp;
    }

    if (k == 1) {
        std::cout << pref_sum[n - 1] << '\n';
        return 0;
    }

    size_t l = 1;
    size_t r = pref_sum[n - 1];
    size_t mid;
    while (r - l > 1) {
        mid = (r + l) / 2;
        if (is_possible(v, pref_sum, mid, k))
            r = mid;
        else
            l = mid;
    }

    std::cout << l << '\n';

    return 0;
}