// url:https://codeforces.com/contest/1485/problem/A
// time:2021-02-12 17:51:43
// name:A-AddandDivide

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
        int a, b;
        std::cin >> a >> b;
        int ans = 1e9;
        for (int i = 0; i < 30; i++) {
            if (b + i == 1) {
                continue;
            }
            int res = i;
            int x = a;
            while (x > 0) {
                x /= b + i;
                res++;
            }
            ans = std::min(ans, res);
        }
        std::cout << ans << "\n";
    }
    return 0;
}
