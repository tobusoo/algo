#include <iostream>
#include <numeric>
#include <vector>

const int base = 31;

std::vector<long long> get_hash(std::string& s)
{
    std::vector<long long> v(s.size() + 1, 0);
    for (size_t i = 1; i <= s.size(); i++) {
        v[i] = (v[i - 1] * base + s[i - 1] - 'a' + 1);
    }

    return v;
}

std::vector<long long> get_base_pow(size_t n)
{
    std::vector<long long> base_pow;
    base_pow.push_back(1);
    base_pow.push_back(base);

    for (size_t i = 1; i < n; i++) {
        base_pow.push_back((base * base_pow[i]));
    }

    return base_pow;
}

int main()
{
    std::string s;
    std::cin >> s;
    size_t n1 = s.length();
    s = s + s;
    size_t n = s.length();

    auto s_hash = get_hash(s);
    auto base_pow = get_base_pow(n);

    size_t best_p = 0;
    for (size_t i = 1; i < n1; i++) {
        long long l = 0, r = n1 - 1;
        size_t res = 0;
        while (l <= r) {
            size_t mid = (l + r) / 2;
            auto hash_best = s_hash[best_p + mid] - s_hash[best_p] * base_pow[mid];
            auto hash_cur = s_hash[i + mid] - s_hash[i] * base_pow[mid];
            if (hash_best == hash_cur) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if (s[best_p + res] > s[i + res])
            best_p = i;
    }

    for (size_t i = 0; i < n1; i++) {
        std::cout << s[best_p];
        best_p = (best_p + 1) % n1;
    }

    std::cout << '\n';

    return 0;
}
