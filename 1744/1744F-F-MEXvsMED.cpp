// url:https://codeforces.com/contest/1744/problem/F
// time:2022-10-18 14:30:30
// name:F-MEXvsMED

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    
    std::vector<int> pre(n + 1), suf(n + 1);
    pre[0] = suf[n] = n;
    for (int i = 0; i < n; i++) {
        pre[i + 1] = std::min(pre[i], p[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = std::min(suf[i + 1], p[i]);
    }
    
    i64 ans = 1;
    
    int l = 0, r = n;
    while (r - l > 1) {
        if (pre[l + 1] > suf[r - 1]) {
            l++;
            ans += std::max(0, std::min(n - l, pre[l] * 2) - (r - l) + 1);
        } else {
            r--;
            ans += std::max(0, std::min(r, suf[r] * 2) - (r - l) + 1);
        }
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
