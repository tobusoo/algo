#include <iostream>
#include <vector>

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
    int n, m;
    std::cin >> n >> m;
    int dsu_size = n * m + 1;
    DSU dsu(dsu_size);
    std::vector<std::vector<int>> ans;

    for (int i = 1; i < dsu_size; i++)
        dsu.make_set(i);

    int act;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int id = (i - 1) * m + j;
            std::cin >> act;
            if (act == 1) {
                dsu.union_set(id, i * m + j);
            } else if (act == 2) {
                dsu.union_set(id, id + 1);
            } else if (act == 3) {
                dsu.union_set(id, id + 1);
                dsu.union_set(id, i * m + j);
            }
        }
    }

    int new_nodes_cnt = 0, cost = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j <= m; j++) {
            int id = (i - 1) * m + j;
            auto a = dsu.find_set(id);
            auto b = dsu.find_set(i * m + j);
            if (a != b) {
                dsu.union_set(id, i * m + j);
                cost++;
                new_nodes_cnt++;
                ans.push_back({i, j, 1});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < m; j++) {
            int id = (i - 1) * m + j;
            auto a = dsu.find_set(id);
            auto b = dsu.find_set(id + 1);
            if (a != b) {
                dsu.union_set(id, id + 1);
                cost += 2;
                new_nodes_cnt++;
                ans.push_back({i, j, 2});
            }
        }
    }

    std::cout << new_nodes_cnt << ' ' << cost << '\n';
    for (auto&& i : ans) {
        for (auto&& j : i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
