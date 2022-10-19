// url:https://codeforces.com/contest/1744/problem/D
// time:2022-10-18 14:12:35
// name:D-Divisibilityby2^n

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    int cur = 0;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        cur += __builtin_ctz(x);
    }
    
    int cnt[20] {};
    for (int i = 1; i <= n; i++) {
        cnt[__builtin_ctz(i)]++;
    }
    
    int ans = 0;
    for (int i = 19; i >= 0; i--) {
        while (cur < n && cnt[i]) {
            cur += i;
            cnt[i]--;
            ans++;
        }
    }
    if (cur < n) {
        ans = -1;
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
