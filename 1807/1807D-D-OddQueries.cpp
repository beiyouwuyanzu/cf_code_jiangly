// url:https://codeforces.com/contest/1807/problem/D
// time:2023-03-20 15:56:51
// name:D-OddQueries

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<i64> s(n + 1);
    for (int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }
    
    while (q--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        l--;
        
        i64 sum = s[l] + s[n] - s[r] + 1LL * k * (r - l);
        std::cout << (sum % 2 ? "YES" : "NO") << "\n";
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
