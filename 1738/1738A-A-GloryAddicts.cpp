//url:https://codeforces.com/contest/1738/problem/A
//time:2022-09-30 17:41:50
//name:A-GloryAddicts

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a[2];
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> y[i];
        a[x[i]].push_back(y[i]);
    }
    
    i64 ans = 0;
    
    std::sort(a[0].begin(), a[0].end(), std::greater());
    std::sort(a[1].begin(), a[1].end(), std::greater());
    
    if (a[0].size() > a[1].size()) {
        std::swap(a[0], a[1]);
    }
    
    if (a[0].size() == a[1].size()) {
        ans = std::accumulate(a[0].begin(), a[0].end() - 1, 0LL) + std::accumulate(a[1].begin(), a[1].end() - 1, 0LL) + std::max(a[0].back(), a[1].back());
    } else {
        ans = std::accumulate(a[0].begin(), a[0].end(), 0LL) + std::accumulate(a[1].begin(), a[1].begin() + a[0].size(), 0LL);
    }
    
    ans += std::accumulate(a[0].begin(), a[0].end(), 0LL);
    ans += std::accumulate(a[1].begin(), a[1].end(), 0LL);
    
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
