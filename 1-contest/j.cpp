#include <iostream>
#include <vector>

size_t diff_sz(size_t a, size_t b)
{
    if (a > b)
        return a - b;
    return b - a;
}

long double arif_sum(size_t first, size_t second, size_t n)
{
    return (long double)((long double)(first + second) / 2 * n);
}

size_t areas_vert_diff(size_t i, size_t n, size_t m)
{
    long double left2 = arif_sum(1, i, i) + arif_sum(m * (n - 1) + 1, m * (n - 1) + i, i);
    left2 = (left2 / 2) * n;
    long double right2 = arif_sum(i + 1, m, m - i) + arif_sum(m * (n - 1) + i + 1, n * m, m - i);
    right2 = (right2 / 2) * n;

    return diff_sz((size_t)left2, (size_t)right2);
}

size_t areas_hor_diff(size_t i, size_t n, size_t m)
{
    size_t up2 = ((double)(1 + m * i) / 2) * m * i;
    size_t down2 = (double)((i * m + 1 + m * n)) / 2 * m * (n - i);

    return diff_sz(up2, down2);
}

void query(int n, int m)
{
    size_t vert_min = SIZE_MAX, hor_min = SIZE_MAX;
    int vert_id_min = 0;
    int hor_id_min = 0;

    int l = 1, r = m;
    if (m == 2) {
        vert_min = areas_vert_diff(1, n, m);
        vert_id_min = 2;
    } else if (m != 1) {
        while (r - l > 1) {
            int mid = (l + r) / 2;
            size_t diff = areas_vert_diff(mid, n, m);
            size_t next_diff = areas_vert_diff(mid + 1, n, m);
            if (diff < vert_min) {
                vert_min = diff;
                vert_id_min = mid + 1;
            }
            if (next_diff < vert_min) {
                vert_min = next_diff;
                vert_id_min = mid + 2;
            }

            if (next_diff < diff) {
                l = mid;
            } else {
                r = mid;
            }
        }
    }

    l = 1;
    r = n;
    if (n == 2) {
        hor_min = areas_hor_diff(1, n, m);
        hor_id_min = 2;
    } else if (n != 1) {
        while (r - l > 1) {
            int mid = (l + r) / 2;
            size_t diff = areas_hor_diff(mid, n, m);
            size_t next_diff = areas_hor_diff(mid + 1, n, m);
            if (diff < hor_min) {
                hor_min = diff;
                hor_id_min = mid + 1;
            }
            if (next_diff < hor_min) {
                hor_min = next_diff;
                hor_id_min = mid + 2;
            }

            if (next_diff < diff) {
                l = mid;
            } else {
                r = mid;
            }
        }
    }
    if (hor_min >= vert_min) {
        std::cout << "V " << vert_id_min << '\n';
    } else
        std::cout << "H " << hor_id_min << '\n';
}

int main()
{
    size_t t;
    std::cin >> t;
    for (size_t i = 0; i < t; i++) {
        size_t n, m;
        std::cin >> n >> m;
        query(n, m);
    }

    return 0;
}