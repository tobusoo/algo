#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    size_t s_in_day = 60 * 60 * 24;
    size_t n;
    std::cin >> n;
    std::vector<int> v(s_in_day, 0);
    int sh, sm, ss, eh, em, es;

    size_t all_day_work = 0;
    size_t night_work = 0;

    for (size_t i = 0; i < n; i++) {
        std::cin >> sh >> sm >> ss >> eh >> em >> es;
        size_t start = ss + sm * 60 + sh * 60 * 60;
        size_t end = es + em * 60 + eh * 60 * 60;
        if (start == end)
            all_day_work++;
        else if (start > end) {
            night_work++;
            v[start]++;
            v[end]--;
        } else {
            v[start]++;
            v[end]--;
        }
    }

    size_t ans = 0;
    size_t current_work = all_day_work + night_work;
    for (size_t i = 0; i < s_in_day; i++) {
        current_work += v[i];
        if (current_work == n) {
            ans++;
        }
    }

    std::cout << ans << '\n';

    return 0;
}