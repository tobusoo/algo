#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

class Stack {
private:
    struct data {
        int num = INT32_MAX;
        int cnt = INT32_MAX;
    };

    std::list<data> l;

    void print_l()
    {
        for (auto&& i : l) {
            printf("%d %d\n", i.num, i.cnt);
        }

        printf("\n");
    }

public:
    int push(int i)
    {
        int del = 0;
        if (l.size() == 0)
            l.push_back({i, 1});
        else if (l.back().num == i)
            l.push_back({i, l.back().cnt + 1});
        else {
            auto t = l.back().cnt;
            if (t >= 3) {
                for (int i = 0; i < t; i++) {
                    l.pop_back();
                    del++;
                }
            }
            if (l.back().num == i)
                l.push_back({i, l.back().cnt + 1});
            else
                l.push_back({i, 1});
        }

        // print_l();
        return del;
    }

    int check()
    {
        auto t = l.back().cnt;
        if (t >= 3) {
            return t;
        }
        return 0;
    }

    void pop()
    {
        l.pop_back();
    }

    int top()
    {
        return l.back().num;
    }

    bool is_empty()
    {
        return l.size() == 0;
    }
};

int main()
{
    Stack s;
    size_t n;
    std::cin >> n;
    int dele = 0;
    for (size_t i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        dele += s.push(temp);
    }
    dele += s.check();

    std::cout << dele << '\n';

    return 0;
}