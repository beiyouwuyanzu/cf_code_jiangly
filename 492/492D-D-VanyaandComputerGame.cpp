// url:https://codeforces.com/contest/492/problem/D
// time:2021-06-24 18:40:24
// name:D-VanyaandComputerGame

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, x, y;
    std::cin >> n >> x >> y;
    while (n--) {
        int a;
        std::cin >> a;
        a = (a - 1) % (x + y) + 1;
        int lo = 1, hi = y;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (mid + i64(mid) * x / y >= a) {
                hi = mid;
            } else {
                lo = mid + 1;
            }
        }
        if (lo - 1 + (i64(lo) * x - 1) / y >= a) {
            std::cout << "Vanya\n";
        } else if (i64(lo) * x % y == 0) {
            std::cout << "Both\n";
        } else {
            std::cout << "Vova\n";
        }
    }
    return 0;
}
