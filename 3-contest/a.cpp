#include <iostream>
#include <queue>
#include <vector>

class Graph {
public:
    std::vector<std::vector<size_t>> g;
    size_t n = 0;

    Graph(size_t n) : g(n, std::vector<size_t>()), n(n)
    {
    }

    void add(size_t i, size_t j)
    {
        g[i].push_back(j);
        g[j].push_back(i);
    }
};

size_t bfs(Graph g, size_t src)
{
    std::queue<size_t> q;
    size_t n = g.n;
    std::vector<size_t> d(n, SIZE_MAX);
    size_t u, v;

    d[src] = 0;
    q.push(src);
    size_t max = 0;

    while (q.size()) {
        u = q.front();
        q.pop();
        for (size_t i = 0; i < g.g[u].size(); i++) {
            v = g.g[u][i];
            if (d[v] == SIZE_MAX) {
                d[v] = d[u] + 1;
                q.push(v);
                max = std::max(max, d[v]);
            }
        }
    }

    return max;
}

int main()
{
    size_t n, predok;
    std::cin >> n;
    std::cin >> predok;
    Graph graph(n);

    size_t i = 1;
    graph.add(i, predok);

    std::vector<std::pair<size_t, size_t>> res(n, {0, -1});
    res[i].first = res[predok].first + 1;
    res[i].second = predok;
    size_t height = 1;
    size_t j = 1;

    for (size_t i = 2; i < n; i++) {
        std::cin >> predok;
        res[i].first = res[predok].first + 1;
        res[i].second = predok;
        if (res[i].first > height) {
            height = res[i].first;
            j = i;
        }
        graph.add(i, predok);
    }

    size_t max = std::max(height, bfs(graph, j));
    std::cout << height << ' ' << max << '\n';
    for (auto&& [deep, predok] : res) {
        std::cout << deep << ' ';
    }

    std::cout << '\n';
    return 0;
}