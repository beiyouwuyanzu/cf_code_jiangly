// url:https://codeforces.com/contest/1485/problem/C
// time:2021-02-12 18:03:39
// name:C-FloorandMod

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int x, y;
        std::cin >> x >> y;
        i64 ans = 0;
        for (int i = 1; i * (i + 1) <= x; i++) {
            int r = std::min(y, x / i - 1);
            ans += std::max(0, r - i);
        }
        std::cout << ans << "\n";
    }
    return 0;
}
