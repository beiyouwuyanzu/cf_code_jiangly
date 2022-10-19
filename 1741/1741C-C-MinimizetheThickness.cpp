// url:https://codeforces.com/contest/1741/problem/C
// time:2022-10-11 17:46:24
// name:C-MinimizetheThickness

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> s(n + 1);
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }
    
    int ans = n;
    for (int i = 1; i <= n; i++) {
        int res = i;
        int k = i;
        for (int j = i + 1; j <= n; j++) {
            if (s[j] == s[k] + s[i]) {
                res = std::max(res, j - k);
                k = j;
            }
        }
        if (k == n) {
            ans = std::min(ans, res);
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

