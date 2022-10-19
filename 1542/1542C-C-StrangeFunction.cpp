// url:https://codeforces.com/contest/1542/problem/C
// time:2021-07-03 16:14:00
// name:C-StrangeFunction

#include <bits/stdc++.h>
using i64 = long long;
constexpr int P = 1000000007;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        i64 n;
        std::cin >> n;
        int ans = 0;
        for (i64 x = 1, i = 1; x <= n; x = std::lcm(i, x), i++) {
            ans = (ans + n / x) % P;
        }
        std::cout << ans << "\n";
    }
    return 0;
}
