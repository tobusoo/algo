#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

#define INF LONG_LONG_MAX
using ll = long long;
using ull = long long;

struct Edge {
    ll from;
    ll to;
    ll w;
};

struct DSU {
    std::vector<int> parent;
    std::vector<int> size;

    DSU(int n) : parent(n, 0), size(n, 0)
    {
    }

    void make_set(int v)
    {
        parent[v] = v;
        size[v] = 1;
    }

    int find_set(int v)
    {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_set(int a, int b)
    {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b])
                std::swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

int main()
{
    ll n, m, v, u, w;
    std::cin >> n >> m;

    DSU dsu(n + 1);
    for (ll i = 0; i < n; i++) {
        dsu.make_set(i + 1);
    }

    std::vector<Edge> e(m);

    for (ll i = 0; i < m; i++) {
        std::cin >> v >> u >> w;
        e[i] = {v, u, w};
    }
    std::sort(e.begin(), e.end(), [](Edge& a, Edge& b) { return a.w < b.w; });

    ull cost = 0;
    for (auto&& edge : e) {
        if (dsu.find_set(edge.from) != dsu.find_set(edge.to)) {
            cost += edge.w;
            dsu.union_set(edge.from, edge.to);
        }
    }

    std::cout << cost << '\n';
    return 0;
}