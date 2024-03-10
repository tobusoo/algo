#include <iostream>
#include <tuple>
#include <vector>

class Graph {
public:
    std::vector<std::vector<std::pair<int, bool>>> g;

    Graph(int n) : g(n, std::vector<std::pair<int, bool>>())
    {
    }

    void add(int i, int j, bool is_left)
    {
        g[i].push_back({j, is_left});
    }

    std::pair<int, int> check_height(int root)
    {
        std::pair<int, int> l = {0, 0};
        std::pair<int, int> r = {0, 0};

        for (auto&& [i, j] : g[root]) {
            if (j == true)
                l = check_height(i);
            else
                r = check_height(i);
        }

        bool flag;
        if (l.second || r.second)
            flag = true;
        else
            flag = std::abs(l.first - r.first) >= 2;

        return std::make_pair(std::max(l.first, r.first) + 1, flag);
    }

    bool check_ordering(int root)
    {
        int l = -1, r = -1;
        for (auto&& [i, j] : g[root]) {
            if (j == true)
                l = i;
            else
                r = i;
        }

        if (l != -1 && root < l) {
            return true;
        }
        if (r != -1 && root > r)
            return true;

        int res = false;
        if (l != -1)
            res += check_ordering(l);
        if (r != -1)
            res += check_ordering(r);

        return res;
    }
};

int main()
{
    int n, root, l, r;
    std::cin >> n;
    std::cin >> root;

    Graph graph(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l >> r;
        if (l != -1)
            graph.add(i, l, true);
        if (r != -1)
            graph.add(i, r, false);
    }

    auto x = graph.check_height(root);
    auto y = graph.check_ordering(root);
    if (x.second)
        std::cout << 0 << '\n';
    else if (y)
        std::cout << 0 << '\n';
    else
        std::cout << 1 << '\n';

    return 0;
}