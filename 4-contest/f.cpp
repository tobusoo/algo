#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;
    long int r, l;

    std::vector<std::pair<long int, bool>> v;

    for (size_t i = 0; i < n; i++) {
        std::cin >> l >> r;
        v.push_back({l, true});
        v.push_back({r, false});
    }

    std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.first < b.first; });

    size_t ans = 0;
    long int start = v[0].first;
    size_t pref_sum = 1;
    bool is_new_start = false;

    for (size_t i = 1; i < v.size(); i++) {
        if (v[i].first == v[i - 1].first) {
            if (v[i].second == true)
                pref_sum++;
            else
                pref_sum--;
            continue;
        }
        if (is_new_start) {
            start = v[i].first;
            is_new_start = false;
        }
        if (v[i].second == true)
            pref_sum++;
        else
            pref_sum--;
        if (pref_sum == 0) {
            ans += v[i].first - start;
            is_new_start = true;
        }
    }

    std::cout << ans << '\n';
    return 0;
}