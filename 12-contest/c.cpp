#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using ll = long long;

int main()
{
    ll n;
    std::cin >> n;
    std::vector<std::pair<ll, bool>> primes(n + 1);
    for (ll i = 2; i < n; i++)
        primes[i] = {i, true};
    primes[0] = primes[1] = {0, false};

    for (ll i = 0; i < n; i++) {
        auto [prime, is_prime] = primes[i];
        if (is_prime == false)
            continue;
        ll j = 2;
        while (prime * j <= n) {
            primes[prime * j].second = false;
            j++;
        }
    }

    std::set<ll> set_primes;
    for (auto&& [x, is_prime] : primes) {
        if (is_prime)
            set_primes.insert(x);
    }

    for (auto&& x : set_primes) {
        ll need = n - x;
        if (set_primes.find(need) != set_primes.end()) {
            std::cout << x << ' ' << need << '\n';
            break;
        }
    }

    return 0;
}