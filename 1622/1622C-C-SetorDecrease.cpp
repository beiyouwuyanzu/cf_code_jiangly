//url:https://codeforces.com/contest/1622/problem/C
//time:2022-06-09 15:50:52
//name:C-SetorDecrease

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    i64 k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    
    i64 ans = 1E18;
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
        
        i64 cur = sum + 1LL * (n - i - 1) * a[0];
        cur = std::max(0LL, cur - k);
        ans = std::min(ans, n - i - 1 + (cur + n - i - 1) / (n - i));
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
