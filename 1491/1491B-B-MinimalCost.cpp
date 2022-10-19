// url:https://codeforces.com/contest/1491/problem/B
// time:2021-02-28 16:44:40
// name:B-MinimalCost

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
        int n, u, v;
        std::cin >> n >> u >> v;
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        int mx = 0;
        for (int i = 0; i < n - 1; i++) {
            mx = std::max(mx, std::abs(a[i] - a[i + 1]));
        }
        if (mx > 1) {
            std::cout << "0\n";
        } else if (mx == 1) {
            std::cout << std::min(u, v) << "\n";
        } else {
            std::cout << std::min(u + v, 2 * v) << "\n";
        }
    }
    return 0;
}

