#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>

using ull = unsigned long long;

ull log_pow(ull ex)
{
    ull res = 1;
    ull base = 31;
    while (ex > 0) {
        if (ex % 2) {
            res = res * base;
        }
        base *= base;
        ex /= 2;
    }

    return res;
}

struct VecPolyHash {
    std::vector<ull> sum_pref;

    VecPolyHash(const std::vector<size_t>& v) : sum_pref(v.size() + 1, 0)
    {
        size_t n = v.size();

        for (size_t i = 0; i < n; i++) {
            sum_pref[i + 1] = sum_pref[i] + log_pow(v[i]);
        }
    }

    ull operator()(size_t pos, size_t len)
    {
        ull sum = sum_pref[pos + len] - sum_pref[pos];

        return sum;
    }
};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, temp;

    std::cin >> n;
    std::vector<size_t> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        a[i] = temp;
    }

    std::cin >> m;
    std::vector<size_t> b(n);
    for (int i = 0; i < m; i++) {
        std::cin >> temp;
        b[i] = temp;
    }

    VecPolyHash hash_a(a), hash_b(b);
    int max_len = std::min(n, m);
    int ans = max_len;
    bool is_find_max = false;

    for (int len = max_len; len > 0 && !is_find_max; --len) {
        for (int j = 0; j + len <= n && !is_find_max; j++) {
            auto s1 = hash_a(j, len);
            for (int k = 0; k + len <= n && !is_find_max; k++) {
                auto s2 = hash_b(k, len);

                if (s1 == s2) {
                    is_find_max = true;
                    ans = len;
                    break;
                }
            }
        }
    }

    if (is_find_max)
        printf("%d\n", ans);
    else
        printf("%d\n", 0);

    return 0;
}
