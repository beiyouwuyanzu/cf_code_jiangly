// url:https://codeforces.com/contest/1806/problem/B
// time:2023-03-20 20:52:07
// name:B-MexMaster

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int cnt0 = std::count(a.begin(), a.end(), 0);
    
    if (cnt0 * 2 - 1 <= n) {
        std::cout << 0 << "\n";
        return;
    }
    
    int cnt1 = std::count(a.begin(), a.end(), 1);
    if (cnt0 + cnt1 == n && cnt1 > 0) {
        std::cout << 2 << "\n";
    } else {
        std::cout << 1 << "\n";
    }
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
