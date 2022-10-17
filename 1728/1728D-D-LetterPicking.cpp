//url:https://codeforces.com/contest/1728/problem/D
//time:2022-09-08 17:56:16
//name:D-LetterPicking

#include <bits/stdc++.h>

using i64 = long long;

int cmp(char a, char b) {
    if (a < b) {
        return -1;
    } else if (a == b) {
        return 0;
    } else {
        return 1;
    }
}

void solve() {
    std::string s;
    std::cin >> s;
    
    int n = s.length();
    
    std::vector dp(n + 1, std::vector<int>(n + 1));
    for (int r = 0; r <= n; r++) {
        for (int l = r; l >= 0; l--) {
            if (l == r) {
                dp[l][r] = 0;
            } else if (r - l >= 2) {
                int v1 = dp[l + 1][r - 1] != 0 ? dp[l + 1][r - 1] : cmp(s[l], s[r - 1]);
                int v2 = dp[l + 2][r] != 0 ? dp[l + 2][r] : cmp(s[l], s[l + 1]);
                int v3 = dp[l + 1][r - 1] != 0 ? dp[l + 1][r - 1] : cmp(s[r - 1], s[l]);
                int v4 = dp[l][r - 2] != 0 ? dp[l][r - 2] : cmp(s[r - 1], s[r - 2]);
                dp[l][r] = std::min(std::max(v1, v2), std::max(v3, v4));
            }
        }
    }
    
    int ans;
    
    if (n % 2 == 0) {
        ans = dp[0][n];
    } else {
        ans = std::min(dp[0][n - 1], dp[1][n]);
        if (ans == 0) {
            ans = 1;
        }
    }
    
    std::cout << (ans == -1 ? "Alice" : ans == 0 ? "Draw" : "Bob") << "\n";
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
