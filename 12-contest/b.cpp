#include <cmath>
#include <iostream>
using ll = long long;

int main()
{
    ll n;
    std::cin >> n;
    ll lim = std::sqrt(n);
    for (ll i = 2; i <= lim; i++) {
        ll cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        if (cnt > 1 && n != 1)
            std::cout << i << '^' << cnt << '*';
        else if (cnt > 1)
            std::cout << i << '^' << cnt;
        else if (cnt == 1 && n != 1)
            std::cout << i << "*";
        else if (cnt == 1)
            std::cout << i;
    }

    if (n != 1)
        std::cout << n;
    std::cout << '\n';
    return 0;
}