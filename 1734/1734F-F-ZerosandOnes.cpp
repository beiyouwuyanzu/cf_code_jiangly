//url:https://codeforces.com/contest/1734/problem/F
//time:2022-09-23 15:57:41
//name:F-ZerosandOnes

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    i64 n, m;
    std::cin >> n >> m;
    
    std::array<std::array<std::array<i64, 2>, 2>, 2> dp {};
    dp[0][0][0] = 1;
    
    for (int i = 0; i < 61; i++) {
        std::array<std::array<std::array<i64, 2>, 2>, 2> g {};
        
        for (auto less : {0, 1}) {
            for (auto carry : {0, 1}) {
                for (auto diff : {0, 1}) {
                    int dm = m >> i & 1, dn = n >> i & 1;
                    for (auto x : {0, 1}) {
                        int nless = x < dm || (x == dm && less);
                        int ncarry = (x + dn + carry) > 1;
                        int ndiff = diff ^ dn ^ carry;
                        g[nless][ncarry][ndiff] += dp[less][carry][diff];
                    }
                }
            }
        }
        dp = g;
    }
    
    std::cout << dp[1][0][1] << "\n";
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
