//url:https://codeforces.com/contest/1697/problem/A
//time:2022-06-12 17:41:00
//name:A-ParkwayWalk

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int sum = std::accumulate(a.begin(), a.end(), 0);
    
    int ans = std::max(0, sum - m);
    
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

