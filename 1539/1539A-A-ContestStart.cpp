// url:https://codeforces.com/contest/1539/problem/A
// time:2021-06-20 13:16:02
// name:A-ContestStart

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int k;
    std::cin >> k;
    while (k--) {
        int n, x, t;
        std::cin >> n >> x >> t;
        int v = t / x;
        if (n <= v) {
            std::cout << i64(n) * (n - 1) / 2 << "\n";
        } else {
            std::cout << i64(v) * (v - 1) / 2 + i64(v) * (n - v) << "\n";
        }
    }
    return 0;
}
