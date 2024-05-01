#include <iostream>
#include <vector>

struct DSU {
    std::vector<int> parent;
    std::vector<int> size;
    std::vector<int> max;
    std::vector<int> min;

    DSU(int n) : parent(n, 0), size(n, 0), max(n, 0), min(n, 0)
    {
    }

    void make_set(int v)
    {
        parent[v] = v;
        size[v] = 1;
        max[v] = v;
        min[v] = v;
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
            max[a] = std::max(max[a], max[b]);
            min[a] = std::min(min[a], min[b]);
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
    DSU dsu(n + 1);
    for (int i = 1; i <= n; i++) {
        dsu.make_set(i);
    }

    std::string action;
    int v1, v2;
    for (int i = 0; i < m; i++) {
        std::cin >> action;
        if (action == "get") {
            std::cin >> v1;
            auto p = dsu.find_set(v1);
            std::cout << dsu.min[p] << ' ' << dsu.max[p] << ' ' << dsu.size[p] << '\n';
        } else {
            std::cin >> v1 >> v2;
            dsu.union_set(v1, v2);
        }
    }

    return 0;
}