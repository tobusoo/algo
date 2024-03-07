#include <iostream>
#include <map>
#include <queue>
#include <tuple>

int main()
{
    size_t temp = 0, n;
    char ch;
    std::cin >> n;
    std::deque<int> q1;
    std::deque<int> q2;

    for (size_t i = 0; i < n; i++) {
        std::cin >> ch;
        switch (ch) {
        case '+':
            std::cin >> temp;
            q2.push_back(temp);
            break;
        case '*':
            std::cin >> temp;
            q2.push_front(temp);
            break;
        case '-':
            std::cout << q1.front() << '\n';
            q1.pop_front();
        default:
            break;
        }
        if (q1.size() < q2.size()) {
            auto g = q2.front();
            q2.pop_front();
            q1.push_back(g);
        }
    }

    return 0;
}