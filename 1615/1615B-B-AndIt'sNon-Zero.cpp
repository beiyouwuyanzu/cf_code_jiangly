//url:https://codeforces.com/contest/1615/problem/B
//time:2021-12-24 17:39:46
//name:B-AndIt'sNon-Zero

#include <bits/stdc++.h>

using i64 = long long;

int sum[20][200001];

void solve() {
    int l, r;
    std::cin >> l >> r;
    
    int ans = 0;
    for (int i = 0; i < 20; i++) {
        ans = std::max(ans, sum[i][r] - sum[i][l - 1]);
    }
    ans = r - l + 1 - ans;
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    for (int c = 0; c < 20; c++) {
        for (int i = 1; i <= 200000; i++) {
            sum[c][i] = sum[c][i - 1] + (i >> c & 1);
        }
    }
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

