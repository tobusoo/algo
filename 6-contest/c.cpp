#include <iostream>
#include <vector>

std::vector<size_t> r_top_sort;

class Graph {
public:
    std::vector<std::vector<size_t>> g;
    std::vector<int> color;
    size_t n = 0;

    Graph(size_t n) : g(n, std::vector<size_t>()), color(n, 0), n(n)
    {
    }

    void add(size_t i, size_t j)
    {
        g[i].push_back(j);
    }

    void dfs(size_t v)
    {
        if (color[v] == 2)
            return;
        color[v] = 1;
        for (size_t i = 0; i < g[v].size(); ++i) {
            size_t to = g[v][i];
            if (color[to] == 0)
                dfs(to);
            else if (color[to] == 1) {
                return;
            }
        }

        r_top_sort.push_back(v);
        color[v] = 2;
    }
};

int main()
{
    size_t n, m;
    std::cin >> n >> m;
    Graph g(n);
    size_t u, v;

    for (size_t i = 0; i < m; i++) {
        std::cin >> u >> v;
        g.add(u - 1, v - 1);
    }

    std::vector<size_t> mb_top_sort(n, 0);
    for (size_t i = 0; i < n; i++) {
        std::cin >> u;
        mb_top_sort[i] = u;
    }

    for (size_t i = 0; i < n; i++) {
        g.dfs(i);
    }

    for (size_t i = 0; i < n; i++) {
        if (mb_top_sort[i] != r_top_sort[n - i - 1] + 1) {
            std::cout << "NO\n";
            return 0;
        }
    }

    std::cout << "YES\n";

    return 0;
}