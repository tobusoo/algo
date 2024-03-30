#include <iostream>
#include <vector>

bool is_loop = false;

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
        if (is_loop)
            return;
        color[v] = 1;
        for (size_t i = 0; i < g[v].size(); ++i) {
            size_t to = g[v][i];
            if (color[to] == 0)
                dfs(to);
            else if (color[to] == 1) {
                is_loop = true;
                return;
            }
        }

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

    for (size_t i = 0; i < n && !is_loop; i++) {
        g.dfs(i);
    }

    if (is_loop)
        printf("1\n");
    else
        printf("0\n");

    return 0;
}
