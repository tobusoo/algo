#include <iostream>
#include <stack>
#include <vector>

int main()
{
    size_t n;
    std::cin >> n;
    std::stack<int> s;

    size_t actions = 0;
    std::vector<std::pair<int, int>> act;
    std::vector<int> v;
    size_t counter_1 = 0;
    size_t counter_2 = 0;

    int prev_n;
    int cur_n;
    std::cin >> cur_n;
    s.push(cur_n);

    counter_1++;
    prev_n = cur_n;

    for (size_t i = 1; i < n; i++) {
        std::cin >> cur_n;
        if (cur_n > prev_n && s.size()) {
            auto t = s.top();
            v.push_back(t);
            s.pop();
            counter_2++;
            while (s.size() && t == s.top() - 1) {
                counter_2++;
                t = s.top();
                s.pop();
                v.push_back(t);
            }

            act.push_back({1, counter_1});
            act.push_back({2, counter_2});
            actions += 2;

            s.push(cur_n);
            counter_2 = 0;
            counter_1 = 1;
        } else {
            s.push(cur_n);
            counter_1++;
        }
        prev_n = cur_n;
    }

    if (s.size() != 0) {
        auto t = s.top();
        s.pop();
        v.push_back(t);

        counter_2++;
        while (s.size() && t == s.top() - 1) {
            counter_2++;
            t = s.top();
            s.pop();
            v.push_back(t);
        }
        act.push_back({1, counter_1});
        act.push_back({2, counter_2});

        actions += 2;
    }
    if (s.size() != 0) {
        std::cout << 0 << '\n';
        return 0;
    }
    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] != v[i - 1] + 1) {
            std::cout << 0 << '\n';
            return 0;
        }
    }

    std::cout << actions << '\n';
    for (auto&& [a, b] : act) {
        std::cout << a << ' ' << b << '\n';
    }

    return 0;
}