#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

int main()
{
    size_t n, c;
    std::cin >> n >> c;

    std::vector<std::vector<size_t>> v;
    size_t s, t;
    for (size_t i = 0; i < n; i++) {
        std::cin >> s >> t;
        v.push_back({s, s + t, i + 1});
    }

    std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a[1] < b[1]; });

    size_t ans = c;
    size_t count = 1;
    std::vector<size_t> tasks;
    size_t r = v[0][1];
    tasks.push_back(v[0][2]);

    for (size_t i = 1; i < n; i++) {
        if (r <= v[i][0]) {
            r = v[i][1];
            ans += c;
            count++;
            tasks.push_back(v[i][2]);
        }
    }

    std::cout << ans << '\n';
    std::cout << count << '\n';
    for (auto&& i : tasks) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}