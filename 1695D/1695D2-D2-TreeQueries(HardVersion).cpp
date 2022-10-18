//url:https://codeforces.com/contest/1695/problem/D2
//time:2022-06-18 18:02:21
//name:D2-TreeQueries(HardVersion)

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    
    if (n == 1) {
        std::cout << "0\n";
        return;
    }
    
    if (std::all_of(adj.begin(), adj.end(), [&](auto a) { return a.size() <= 2; })) {
        std::cout << "1\n";
        return;
    }
    
    int ans = 0;
    std::vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (adj[i].size() == 1) {
            ans++;
            int j = adj[i][0], k = i;
            while (adj[j].size() <= 2) {
                k ^= adj[j][0] ^ adj[j][1];
                std::swap(j, k);
            }
            if (!vis[j]) {
                vis[j] = true;
                ans--;
            }
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

