// url:https://codeforces.com/contest/1542/problem/B
// time:2021-07-03 16:11:36
// name:B-PlusandMultiply

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int a, b, n;
        std::cin >> n >> a >> b;
        bool ok = false;
        for (i64 x = 1; x <= n; x *= a) {
            if ((n - x) % b == 0) {
                ok = true;
            }
            if (a == 1) {
                break;
            }
        }
        if (ok) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
    }
    return 0;
}
