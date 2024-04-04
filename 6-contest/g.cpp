#include <iostream>
#include <vector>

#define INF 999999

class Graph {
public:
    size_t n;
    std::vector<std::vector<int>> g;

    Graph(int n) : n(n), g(n, std::vector<int>(n, INF))
    {
    }

    void add(int i, int j, int w)
    {
        g[i][j] = w;
        g[j][i] = w;
    }

    void Floyd()
    {
        for (size_t k = 0; k < n; k++) {
            for (size_t i = 0; i < n; i++) {
                for (size_t j = 0; j < n; j++) {
                    g[i][j] = std::min(g[i][j], g[i][k] + g[k][j]);
                }
            }
        }
    }

    void print()
    {
        for (auto&& i : g) {
            for (auto&& j : i) {
                printf("%d ", j);
            }
            printf("\n");
        }
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    Graph g(n);
    int u, v, w;

    for (int i = 0; i < m; i++) {
        std::cin >> u >> v >> w;
        g.add(u - 1, v - 1, w);
    }

    g.Floyd();
    int ans = -1;
    int min = 9999999;
    for (int i = 0; i < n; i++) {
        int cur_max = g.g[i][0];
        for (int j = 1; j < n; j++) {
            cur_max = std::max(cur_max, g.g[i][j]);
        }
        if (cur_max < min) {
            min = cur_max;
            ans = i + 1;
        }
    }

    std::cout << ans << '\n';
    return 0;
}
