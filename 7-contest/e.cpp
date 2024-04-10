#include <iostream>
#include <map>

int main()
{
    std::string a, b;
    std::cin >> a >> b;
    int a_len = a.length();
    int b_len = b.length();

    std::map<std::pair<int, int>, int> m;
    for (int i = -1; i < a_len + 1; i++) {
        m[{i, -1}] = i + 1;
    }
    for (int i = -1; i < b_len + 1; i++) {
        m[{-1, i}] = i + 1;
    }

    for (int i = 0; i < a_len; i++) {
        for (int j = 0; j < b_len; j++) {
            int cost = 0;

            if (a[i] != b[j])
                cost = 1;

            m[{i, j}] = std::min(m[{i - 1, j}] + 1, m[{i, j - 1}] + 1);
            m[{i, j}] = std::min(m[{i, j}], m[{i - 1, j - 1}] + cost);

            if (i && j && a[i] == b[j - 1] && a[i - 1] == b[j]) {
                m[{i, j}] = std::min(m[{i, j}], m[{i - 2, j - 2}] + 1);
            }
        }
    }

    std::cout << m[{a_len - 1, b_len - 1}] << '\n';
    return 0;
}