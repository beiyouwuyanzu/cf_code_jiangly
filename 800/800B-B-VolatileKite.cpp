//url:https://codeforces.com/contest/800/problem/B
//time:2021-01-03 15:45:02
//name:B-VolatileKite

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    double ans = 1e10;
    for (int i = 0; i < n; i++) {
        int u = (i - 1 + n) % n, v = (i + 1) % n;
        ans = std::min(ans, (i64(x[u] - x[i]) * (y[v] - y[i]) - i64(x[v] - x[i]) * (y[u] - y[i])) / std::sqrt(i64(x[u] - x[v]) * (x[u] - x[v]) + i64(y[u] - y[v]) * (y[u] - y[v])));
    }
    std::cout << std::fixed << std::setprecision(10) << ans / 2 << "\n";
    return 0;
}
