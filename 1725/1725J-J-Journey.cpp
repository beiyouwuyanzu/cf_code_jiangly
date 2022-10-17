//url:https://codeforces.com/contest/1725/problem/J
//time:2022-09-04 18:13:27
//name:J-Journey

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<std::array<int, 2>>> adj(n);
    i64 sum = 0;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        sum += w;
    }
    
    std::vector<int> parent(n, -1), len(n);
    std::vector<std::array<i64, 3>> dp1(n);
    std::vector<std::array<i64, 2>> dp2(n);
    std::vector<i64> ch(n), dia(n), up1(n), up2(n);
    
    std::function<void(int)> dfs1 = [&](int x) {
        for (auto [y, w] : adj[x]) {
            if (y == parent[x]) {
                continue;
            }
            parent[y] = x;
            len[y] = w;
            dfs1(y);
            
            i64 u = w + dp1[y][0];
            for (int j = 0; j < 3; j++) {
                if (u > dp1[x][j]) {
                    std::swap(u, dp1[x][j]);
                }
            }
            
            u = dia[y];
            for (int j = 0; j < 2; j++) {
                if (u > dp2[x][j]) {
                    std::swap(u, dp2[x][j]);
                }
            }
        }
        
        ch[x] = dp1[x][0];
        dia[x] = std::max(dp2[x][0], dp1[x][0] + dp1[x][1]);
    };
    dfs1(0);
    
    auto ans = sum * 2;
    std::function<void(int)> dfs2 = [&](int x) {
        i64 u = up1[x] + len[x];
        for (int j = 0; j < 3; j++) {
            if (u > dp1[x][j]) {
                std::swap(u, dp1[x][j]);
            }
        }
        
        for (auto [y, w] : adj[x]) {
            if (y == parent[x]) {
                continue;
            }
            
            up1[y] = std::max(up1[x] + len[x], w + dp1[y][0] == dp1[x][0] ? dp1[x][1] : dp1[x][0]);
            up2[y] = std::max({up2[x], dia[y] == dp2[x][0] ? dp2[x][1] : dp2[x][0], w + dp1[y][0] == dp1[x][0] ? dp1[x][1] + dp1[x][2] :
                w + dp1[y][0] == dp1[x][1] ? dp1[x][0] + dp1[x][2] : dp1[x][0] + dp1[x][1]});
            
            ans = std::min(ans, 2 * sum - 2 * w - dia[y] - up2[y]);
            
            dfs2(y);
        }
    };
    dfs2(0);
    
    for (int x = 0; x < n; x++) {
        if (adj[x].size() < 4) {
            continue;
        }
        
        std::vector<i64> v;
        for (auto [y, w] : adj[x]) {
            if (y == parent[x]) {
                v.push_back(up1[x] + w);
            } else {
                v.push_back(ch[y] + w);
            }
        }
        
        std::nth_element(v.begin(), v.begin() + 4, v.end(), std::greater());
        
        ans = std::min(ans, 2 * sum - std::accumulate(v.begin(), v.begin() + 4, 0LL));
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
