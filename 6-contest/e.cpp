#include <iostream>
#include <vector>

int main()
{
    std::string p, t;
    std::cin >> p >> t;
    std::vector<int> matches;
    size_t n = p.size();
    size_t m = t.size();
    if (n > m) {
        std::cout << 0 << '\n';
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < m - n + 1; i++) {
        count = 0;
        for (size_t j = 0; j < n; j++) {
            if (p[j] != t[i + j]) {
                count++;
                if (count > 1)
                    break;
            }
        }
        if (count <= 1)
            matches.push_back(i + 1);
    }

    std::cout << matches.size() << '\n';
    for (auto&& i : matches) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}