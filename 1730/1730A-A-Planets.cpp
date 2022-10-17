//url:https://codeforces.com/contest/1730/problem/A
//time:2022-09-25 17:55:11
//name:A-Planets

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, c;
    std::cin >> n >> c;
    
    std::vector<int> a(n);
    std::map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }
    
    int ans = 0;
    for (auto [_, x] : cnt) {
        ans += std::min(x, c);
    }
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
