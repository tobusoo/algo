#include <iostream>

void query(int x)
{
    printf("%d\n", x);
    fflush(stdout);
}

int request()
{
    std::string str;
    std::cin >> str;
    if (str == "<")
        return -1;
    else
        return 1;
}

int main()
{
    size_t n = 0;
    std::cin >> n;

    int l = 0, r = n + 1;
    int mid = 0;

    while (r - l > 1) {
        mid = (l + r) / 2;
        query(mid);
        if (request() == -1) {
            r = mid;
        } else {
            l = mid;
        }
    }
    printf("! %d\n", l);

    return 0;
}