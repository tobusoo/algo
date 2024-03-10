#include <iostream>
#include <queue>
#include <vector>

size_t request(std::vector<std::pair<size_t, size_t>>& res, size_t u, size_t v)
{
    size_t h1 = res[u].first;
    size_t h2 = res[v].first;
    while (h1 != h2) {
        if (h1 > h2) {
            u = res[u].second;
            h1--;
        } else {
            v = res[v].second;
            h2--;
        }
    }

    while (u != v) {
        u = res[u].second;
        v = res[v].second;
    }

    return u;
}

int main()
{
    size_t n, predok, m;
    std::cin >> n;
    std::cin >> predok;

    size_t i = 1;

    std::vector<std::pair<size_t, size_t>> res(n, {0, -1});
    res[i].first = res[predok].first + 1;
    res[i].second = predok;

    for (i = 2; i < n; i++) {
        std::cin >> predok;
        res[i].first = res[predok].first + 1;
        res[i].second = predok;
    }
    std::cin >> m;

    size_t u, v;
    for (i = 0; i < m; i++) {
        std::cin >> u >> v;
        std::cout << request(res, u, v) << '\n';
    }

    return 0;
}