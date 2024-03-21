#include <iostream>
#include <vector>

const int base = 31;

std::vector<long long int> get_hash(std::string& s)
{
    std::vector<long long int> v(s.size() + 1, 0);
    for (size_t i = 1; i <= s.size(); i++) {
        v[i] = (v[i - 1] * base + s[i - 1] - 'a' + 1);
    }

    return v;
}

long long int get_hash_value(std::string& s)
{
    long long int hash = 0;

    for (size_t i = 1; i <= s.size(); i++) {
        hash = (hash * base + s[i - 1] - 'a' + 1);
    }

    return hash;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string t, s;
    std::cin >> t;
    size_t t_len = t.size();

    std::vector<long long int> base_pow;
    base_pow.push_back(1);
    base_pow.push_back(base);

    for (size_t i = 1; i < t_len; i++) {
        base_pow.push_back((base * base_pow[i]));
    }
    auto t_hash = get_hash(t);

    size_t q;
    std::cin >> q;
    long long int hash_1;

    long long int s_hash;
    size_t s_len = 0;
    size_t count = 0;

    for (size_t i = 0; i < q; i++) {
        std::cin >> s;
        s_hash = get_hash_value(s);
        s_len = s.size();
        count = 0;
        std::vector<size_t> res;
        if (s_len > t_len) {
            std::cout << 0 << '\n';
            continue;
        }

        for (size_t j = 0; j <= t_len - s_len; j++) {
            hash_1 = (t_hash[s_len + j] - t_hash[j] * base_pow[s_len]);
            if (hash_1 == s_hash) {
                res.push_back(j);
                count++;
            }
        }
        std::cout << count << ' ';
        if (count) {
            for (auto&& val : res) {
                std::cout << val << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}