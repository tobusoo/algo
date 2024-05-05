#include <iostream>
#include <map>
#include <set>
#include <vector>

using ll = long long;

int main()
{
    ll n;
    std::cin >> n;
    std::vector<ll> a(n);
    std::vector<ll> d(n);
    std::vector<ll> prev(n);
    std::vector<ll> next(n);

    for (ll i = 0; i < n; i++) {
        std::cin >> a[i];
        prev[i] = i - 1;
        next[i] = i + 1;
    }
    next[n - 1] = prev[0] = -1;

    for (ll i = 0; i < n; i++)
        std::cin >> d[i];

    std::set<ll> alive;
    for (ll i = 0; i < n; i++)
        alive.insert(i);

    for (ll i = 0; i < n; i++) {
        std::set<ll> die;

        for (auto&& monster : alive) {
            ll damage = 0;
            if (next[monster] != -1)
                damage += a[next[monster]];
            if (prev[monster] != -1)
                damage += a[prev[monster]];
            if (damage > d[monster]) {
                die.insert(monster);
            }
        }

        std::cout << die.size() << ' ';
        alive.clear();
        for (auto&& i : die) {
            if (prev[i] != -1) {
                next[prev[i]] = next[i];
                if (die.find(prev[i]) == die.end())
                    alive.insert(prev[i]);
            }
            if (next[i] != -1) {
                prev[next[i]] = prev[i];
                if (die.find(next[i]) == die.end())
                    alive.insert(next[i]);
            }
        }
    }
    std::cout << '\n';

    return 0;
}