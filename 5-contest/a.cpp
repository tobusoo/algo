#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string s;
    std::cin >> s;

    int base = 31;
    std::vector<long long int> base_pow;
    base_pow.push_back(1);
    base_pow.push_back(base);

    for (size_t i = 1; i < s.size(); i++) {
        base_pow.push_back((base * *base_pow.rbegin()));
    }

    std::vector<long long int> v(s.size() + 1, 0);

    for (size_t i = 1; i <= s.size(); i++) {
        v[i] = (v[i - 1] * base + s[i - 1] - 'a' + 1);
    }

    int m;
    std::cin >> m;
    long long int hash_1;
    long long int hash_2;
    long long int l1, r1, l2, r2;

    for (int i = 0; i < m; i++) {
        std::cin >> l1 >> r1 >> l2 >> r2;
        hash_1 = (v[r1] - v[l1 - 1] * base_pow[r1 - l1 + 1]);
        hash_2 = (v[r2] - v[l2 - 1] * base_pow[r2 - l2 + 1]);

        if (hash_1 == hash_2)
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }

    return 0;
}