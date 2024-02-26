#include <iostream>
#include <list>

class MinStack {
private:
    struct data {
        int i = 0;
        int min = 0;
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

    int min()
    {
        return l.back().min;
    }
};

int main()
{
    size_t n;
    std::cin >> n;
    MinStack stack;

    for (size_t i = 0; i < n; ++i) {
        int oper;
        std::cin >> oper;
        switch (oper) {
        case 1:
            int value;
            std::cin >> value;
            stack.push(value);
            break;
        case 2:
            stack.pop();
            break;
        case 3:
            std::cout << stack.min() << '\n';
            break;
        default:
            break;
        }
    }

    return 0;
}