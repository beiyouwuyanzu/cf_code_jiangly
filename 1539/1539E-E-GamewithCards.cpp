// url:https://codeforces.com/contest/1539/problem/E
// time:2021-06-20 13:59:51
// name:E-GamewithCards

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> k(n), al(n), bl(n), ar(n), br(n);
    for (int i = 0; i < n; i++) {
        std::cin >> k[i];
        std::cin >> al[i] >> bl[i];
        std::cin >> ar[i] >> br[i];
    }
    std::vector<int> ans;
    std::vector<int> cl(n + 1), dl(n + 1), cr(n + 1), dr(n + 1);
    cl[n] = 0;
    dl[n] = m;
    cr[n] = 0;
    dr[n] = m;
    for (int i = n - 1; i >= 0; i--) {
        cl[i] = m + 1;
        dl[i] = 0;
        cr[i] = m + 1;
        dr[i] = 0;
        if (al[i] <= k[i] && k[i] <= bl[i]) {
            if (cl[i + 1] <= k[i] && k[i] <= dl[i + 1]) {
                cr[i] = ar[i];
                dr[i] = br[i];
            } else {
                cr[i] = std::max(ar[i], cr[i + 1]);
                dr[i] = std::min(br[i], dr[i + 1]);
            }
        }
        if (ar[i] <= k[i] && k[i] <= br[i]) {
            if (cr[i + 1] <= k[i] && k[i] <= dr[i + 1]) {
                cl[i] = al[i];
                dl[i] = bl[i];
            } else {
                cl[i] = std::max(al[i], cl[i + 1]);
                dl[i] = std::min(bl[i], dl[i + 1]);
            }
        }
    }
    if ((cl[0] <= 0 && 0 <= dl[0]) || (cr[0] <= 0 && 0 <= dr[0])) {
        std::cout << "Yes\n";
        int x = 0, y = 0;
        for (int i = 0; i < n; i++) {
            if (al[i] <= k[i] && k[i] <= bl[i] && ar[i] <= y && y <= br[i]
                && ((cl[i + 1] <= k[i] && k[i] <= dl[i + 1]) || (cr[i + 1] <= y && y <= dr[i + 1]))) {
                x = k[i];
                std::cout << 0 << " \n"[i == n - 1];
            } else if (al[i] <= x && x <= bl[i] && ar[i] <= k[i] && k[i] <= br[i]
                && ((cl[i + 1] <= x && x <= dl[i + 1]) || (cr[i + 1] <= k[i] && k[i] <= dr[i + 1]))) {
                y = k[i];
                std::cout << 1 << " \n"[i == n - 1];
            } else {
                assert(false);
            }
        }
    } else {
        std::cout << "No\n";
    }
    return 0;
}
