//url:https://codeforces.com/contest/1735/problem/B
//time:2022-10-04 12:03:54
//name:B-TeawithTangerines

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        ans += (a[i] - 1) / (2 * a[0] - 1);
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
