#include <iostream>
#include <stack>
#include <vector>

#define INF -1

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            std::cin >> a[i][j];

    int max_len = 1;
    int ii = 1, jj = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i * j == 0)
                continue;
            if (a[i][j] == 1) {
                a[i][j] = std::min(a[i][j - 1], a[i - 1][j]);
                a[i][j] = std::min(a[i - 1][j - 1], a[i][j]) + 1;
            }
            if (a[i][j] >= max_len) {
                max_len = a[i][j];
                ii = i - max_len + 2;
                jj = j - max_len + 2;
            }
        }
    }

    std::cout << max_len << '\n';
    std::cout << ii << ' ' << jj << '\n';

    return 0;
}