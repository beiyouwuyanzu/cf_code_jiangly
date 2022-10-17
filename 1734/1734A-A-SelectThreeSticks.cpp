//url:https://codeforces.com/contest/1734/problem/A
//time:2022-09-23 15:31:03
//name:A-SelectThreeSticks

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a.begin(), a.end());
    
    int ans = 2E9;
    for (int i = 0; i < n - 2; i++) {
        ans = std::min(ans, a[i + 2] - a[i]);
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
