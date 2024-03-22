#include <algorithm>
#include <iostream>
#include <vector>

using ull = unsigned long long;

struct PolyHash {
    static std::vector<ull> pow;
    static const int base = 31;

    std::vector<ull> pref;

    PolyHash(const std::string& s) : pref(s.size() + 1, 0)
    {
        size_t n = s.size();
        for (size_t i = 0; i < n; i++) {
            pow.push_back(pow.back() * base);
        }

        for (size_t i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + s[i] * pow[i];
        }
    }

    // substr hash
    ull operator()(size_t pos, size_t len, size_t n)
    {
        ull hash = pref[pos + len] - pref[pos];
        hash *= pow[n - (pos + len - 1)];

        return hash;
    }
};

std::vector<ull> PolyHash::pow{1};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string a, b;
    std::cin >> a >> b;
    size_t n = std::max(a.size(), b.size() * 2);

    PolyHash hash_a(a), hash_b(b + b);

    std::vector<ull> hashes;
    for (size_t i = 0; i < b.size(); i++) {
        hashes.push_back(hash_b(i, b.size(), n));
    }
    std::sort(hashes.begin(), hashes.end());

    size_t answ = 0;
    for (size_t i = 0; i + b.size() <= a.size(); i++) {
        answ += std::binary_search(hashes.begin(), hashes.end(), hash_a(i, b.size(), n));
    }

    std::cout << answ << '\n';

    return 0;
}