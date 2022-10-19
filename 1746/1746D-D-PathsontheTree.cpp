// url:https://codeforces.com/contest/1746/problem/D
// time:2022-10-15 17:58:11
// name:D-PathsontheTree

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> p(n), d(n);
    for (int i = 1; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
        d[p[i]]++;
    }
    
    std::vector<int> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        adj[p[i]].push_back(i);
    }
    
    std::vector<std::array<int, 2>> f(n);
    std::vector<std::array<i64, 2>> dp(n);
    std::function<void(int)> dfs = [&](int x) {
        for (auto y : adj[x]) {
            f[y][0] = f[x][0] / d[x];
            f[y][1] = (f[x][1] + d[x] - 1) / d[x];
            dfs(y);
        }
        std::sort(adj[x].begin(), adj[x].end(), [&](int i, int j) {
            return dp[i][1] - dp[i][0] > dp[j][1] - dp[j][0];
        });
        for (auto k : {0, 1}) {
            int t = f[x][k];
            dp[x][k] = 1LL * s[x] * t;
            for (int j = 0; j < d[x]; j++) {
                dp[x][k] += dp[adj[x][j]][f[adj[x][j]][0] * d[x] + j < t];
            }
        }
    };
    f[0] = {k, k};
    dfs(0);
    
    std::cout << dp[0][0] << "\n";
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
