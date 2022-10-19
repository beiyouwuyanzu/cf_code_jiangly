// url:https://codeforces.com/contest/1646/problem/C
// time:2022-03-04 19:47:36
// name:C-FactorialsandPowersofTwo

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    i64 n;
    std::cin >> n;
    
    i64 fac[15];
    fac[0] = 1;
    for (int i = 1; i <= 14; i++) {
        fac[i] = fac[i - 1] * i;
    }
    
    int ans = 100;
    for (int s = 0; s < (1 << 14); s++) {
        i64 m = n;
        for (int i = 0; i < 14; i++) {
            if (s >> i & 1) {
                m -= fac[i + 1];
            }
        }
        if (m >= 0) {
            ans = std::min<int>(ans, __builtin_popcount(s) + __builtin_popcountll(m));
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
