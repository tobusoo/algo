#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n, 0);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> d(n, 1), p(n, -1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i]) {
                if (1 + d[j] > d[i]) {
                    d[i] = 1 + d[j];
                    p[i] = j;
                }
            }
        }
    }

    int ans = d[0];
    int position = 0;
    for (int i = 0; i < n; ++i)
        if (d[i] > ans) {
            ans = d[i];
            position = i;
        }

    std::vector<int> path;
    while (position != -1) {
        path.push_back(position);
        position = p[position];
    }

    std::cout << ans << '\n';
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << a[path[i]] << ' ';
    }
    std::cout << '\n';

    return 0;
}