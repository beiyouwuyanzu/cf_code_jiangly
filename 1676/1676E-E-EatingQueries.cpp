// url:https://codeforces.com/contest/1676/problem/E
// time:2022-05-10 17:54:48
// name:E-EatingQueries

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n), s(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end(), std::greater());
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }
    
    for (int i = 0; i < q; i++) {
        int x;
        std::cin >> x;
        int ans = std::lower_bound(s.begin(), s.end(), x) - s.begin();
        if (ans > n) {
            ans = -1;
        }
        std::cout << ans << "\n";
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
