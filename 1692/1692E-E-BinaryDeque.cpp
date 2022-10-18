//url:https://codeforces.com/contest/1692/problem/E
//time:2022-06-14 17:47:16
//name:E-BinaryDeque

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, s;
    std::cin >> n >> s;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int ans = n + 1;
    
    int cur = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j < n && cur + a[j] <= s) {
            cur += a[j];
            j++;
        }
        if (cur == s) {
            ans = std::min(ans, n - (j - i));
        }
        cur -= a[i];
    }
    
    if (ans > n) {
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

