//url:https://codeforces.com/contest/1606/problem/B
//time:2022-06-10 11:05:14
//name:B-UpdateFiles

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    i64 n, k;
    std::cin >> n >> k;
    
    i64 cur = 1;
    i64 ans = 0;
    while (cur < k) {
        cur *= 2;
        ans++;
    }
    
    if (cur < n) {
        ans += (n - cur + k - 1) / k;
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
