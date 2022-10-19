// url:https://codeforces.com/contest/1495/problem/A
// time:2021-03-10 15:33:43
// name:A-DiamondMiner

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    std::cout << std::fixed << std::setprecision(10);
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a, b;
        for (int i = 0; i < 2 * n; i++) {
            int x, y;
            std::cin >> x >> y;
            if (y == 0) {
                a.push_back(std::abs(x));
            } else {
                b.push_back(std::abs(y));
            }
        }
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());
        double ans = 0;
        for (int i = 0; i < n; i++) {
            ans += std::sqrt(i64(a[i]) * a[i] + i64(b[i]) * b[i]);
        }
        std::cout << ans << "\n";
    }
    return 0;
}

