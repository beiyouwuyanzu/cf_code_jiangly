//url:https://codeforces.com/contest/1730/problem/B
//time:2022-09-25 18:05:20
//name:B-MeetingontheLine

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

void solve() {
    int n;
    std::cin >> n;
    
    int min = inf, max = -inf;
    std::vector<int> x(n), t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> t[i];
        min = std::min(min, x[i] - t[i]);
        max = std::max(max, x[i] + t[i]);
    }
    std::cout << 0.5 * (min + max) << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cout << std::fixed;
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
