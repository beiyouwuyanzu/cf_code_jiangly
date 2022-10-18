//url:https://codeforces.com/contest/1550/problem/E
//time:2021-07-14 18:10:19
//name:E-Stringforces

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::string s;
    std::cin >> s;
    
    int lo = 0, hi = n;
    
    while (lo < hi) {
        int len = (lo + hi + 1) / 2;
        
        std::vector f(k, std::vector<int>(n + 2));
        
        for (int c = 0; c < k; c++) {
            f[c][n] = f[c][n + 1] = n + 1;
            
            for (int i = n - 1, l = 0; i >= 0; i--) {
                if (s[i] == '?' || s[i] == 'a' + c) {
                    l++;
                } else {
                    l = 0;
                }
                
                f[c][i] = (l >= len ? i + len : f[c][i + 1]);
            }
        }
        
        std::vector<int> dp(1 << k, n + 1);
        dp[0] = 0;
        for (int s = 0; s < (1 << k); s++) {
            for (int i = 0; i < k; i++) {
                if (s >> k & 1) {
                    continue;
                }
                
                int t = s | 1 << i;
                dp[t] = std::min(dp[t], f[i][dp[s]]);
            }
        }
        
        if (dp.back() <= n) {
            lo = len;
        } else {
            hi = len - 1;
        }
    }
    
    std::cout << lo << "\n";
    
    return 0;
}

