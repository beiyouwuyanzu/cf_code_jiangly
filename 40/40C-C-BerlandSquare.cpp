// url:https://codeforces.com/contest/40/problem/C
// time:2023-04-23 07:05:36
// name:C-BerlandSquare

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, x, M, y;
    std::cin >> N >> x >> M >> y;
    
    int d = std::abs(x - y);
    if (d > N + M) {
        std::cout << N + M + 1 << "\n";
        return 0;
    }
    
    i64 ans = 2 + N + M;
    for (int i = 1; i <= N; i++) {
        ans -= (std::abs(i - std::min(M, i)) <= d && d <= i + M);
    }
    for (int i = 1; i <= M; i++) {
        ans -= (std::abs(i - std::min(N, i)) <= d && d <= i + N);
    }
    for (int i = 1; i <= N; i++) {
        int lo = std::max({1, d - i, i - d});
        int hi = std::min({M, i + d});
        ans += std::max(0, hi - lo + 1);
        lo = std::max({1, d + 1 - i, i - d + 1});
        hi = std::min({M, i + d - 1});
        ans += std::max(0, hi - lo + 1);
    }
    std::cout << ans << "\n";
    
    return 0;
}
