#include <iostream>
#include <vector>

int main()
{
    size_t n, m, k;
    std::cin >> n >> m >> k;

    std::vector<size_t> res(k, 0);
    size_t temp;

    std::vector<std::vector<size_t>> prefix_sum(n, std::vector<size_t>(m, 0));

    std::cin >> temp;
    prefix_sum[0][0] = temp;
    for (size_t i = 1; i < m; i++) {
        std::cin >> temp;
        prefix_sum[0][i] = prefix_sum[0][i - 1] + temp;
    }

    for (size_t i = 1; i < n; i++) {
        std::cin >> temp;
        prefix_sum[i][0] = temp;
        for (size_t j = 1; j < m; j++) {
            std::cin >> temp;
            prefix_sum[i][j] = prefix_sum[i][j - 1] + temp;
        }
        for (size_t j = 0; j < m; j++) {
            prefix_sum[i][j] += prefix_sum[i - 1][j];
        }
    }

    size_t y1, x1, y2, x2;
    size_t all = 0, left = 0, up = 0, intersec;
    for (size_t i = 0; i < k; i++) {
        std::cin >> y1 >> x1 >> y2 >> x2;
        all = prefix_sum[y2 - 1][x2 - 1];
        if (y1 > 1)
            up = prefix_sum[y1 - 2][x2 - 1];
        else
            up = 0;
        if (x1 > 1)
            left = prefix_sum[y2 - 1][x1 - 2];
        else
            left = 0;
        if (x1 > 1 && y1 > 1)
            intersec = prefix_sum[y1 - 2][x1 - 2];
        else
            intersec = 0;

        res[i] = all - left - up + intersec;
    }

    for (auto&& i : res) {
        std::cout << i << '\n';
    }

    return 0;
}