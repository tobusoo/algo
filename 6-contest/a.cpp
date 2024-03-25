#include <iostream>
#include <set>
#include <vector>

std::vector<std::set<size_t>> comp;

class Graph {
public:
    std::vector<std::vector<size_t>> g;
    std::vector<bool> used;
    size_t n = 0;

    Graph(size_t n) : g(n, std::vector<size_t>()), used(n, false), n(n)
    {
    }

    void add(size_t i, size_t j)
    {
        g[i].push_back(j);
        g[j].push_back(i);
    }

    void dfs(size_t v, std::set<size_t>& comp_s)
    {
        used[v] = true;
        comp_s.insert(v);
        for (size_t i = 0; i < g[v].size(); ++i) {
            size_t to = g[v][i];
            if (!used[to])
                dfs(to, comp_s);
        }
    }

    void find_comps()
    {
        for (size_t i = 0; i < n; ++i)
            used[i] = false;
        for (size_t i = 0; i < n; ++i) {
            if (!used[i]) {
                comp.push_back(std::set<size_t>());
                dfs(i, comp.back());
            }
        }

        std::cout << comp.size() << '\n';
        for (size_t i = 0; i < comp.size(); i++) {
            if (comp[i].size() == 0)
                continue;
            std::cout << comp[i].size() << '\n';
            for (auto&& i : comp[i])
                std::cout << i + 1 << ' ';
            std::cout << '\n';
        }
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

    g.find_comps();
    return 0;
}
