#include <iostream>
#include <list>

class MinStack {
private:
    struct data {
        int i = INT32_MAX;
        int min = INT32_MAX;
    };

    std::list<data> l;

public:
    void push(int i)
    {
        int min;
        if (l.size() != 0)
            min = std::min(l.back().min, i);
        else
            min = i;

        l.push_back({i, min});
    }

    void pop()
    {
        l.pop_back();
    }

    int top()
    {
        return l.back().i;
    }

    int min()
    {
        if (is_empty())
            return INT32_MAX;
        return l.back().min;
    }

    bool is_empty()
    {
        return l.size() == 0;
    }
};

class Queue {
private:
    MinStack s1;
    MinStack s2;

public:
    void push(int value)
    {
        s1.push(value);
    }

    void pop()
    {
        if (s2.is_empty()) {
            while (!s1.is_empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        if (!s2.is_empty())
            s2.pop();
    }

    int min()
    {
        return std::min(s1.min(), s2.min());
    }
};

int main()
{
    size_t n, k;
    std::cin >> n >> k;
    Queue q;
    int temp;

    for (size_t i = 0; i < k; i++) {
        std::cin >> temp;
        q.push(temp);
    }
    std::cout << q.min() << ' ';
    q.pop();

    for (size_t i = 0; i < n - k; i++) {
        std::cin >> temp;
        q.push(temp);
        std::cout << q.min() << ' ';
        q.pop();
    }
    std::cout << '\n';

    return 0;
}