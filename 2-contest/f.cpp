#include <deque>
#include <iostream>
#include <vector>

int main()
{
    size_t n, act;
    int id;
    std::deque<int> d;
    std::cin >> n;
    std::vector<int> v(100000, 0);
    int leave = 0;
    int added = 0;
    std::vector<int> res;

    for (size_t i = 0; i < n; i++) {
        std::cin >> act;
        switch (act) {
        case 1:
            std::cin >> id;
            d.push_back(id);
            v[id] = added++;
            break;
        case 2:
            d.pop_front();
            leave++;
            break;
        case 3:
            d.pop_back();
            added--;
            break;
        case 4:
            std::cin >> id;
            res.push_back(v[id] - leave);
            break;
        case 5:
            res.push_back(d[0]);
            break;
        }
    }

    for (auto&& i : res) {
        std::cout << i << '\n';
    }

    return 0;
}