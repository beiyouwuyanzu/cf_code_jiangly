//url:https://codeforces.com/contest/1693/problem/B
//time:2022-06-16 17:49:23
//name:B-FakePlasticTrees

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int p;
        std::cin >> p;
        p--;
        adj[p].push_back(i);
    }
    
    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> r[i];
    }
    
    int ans = 0;
    std::function<int(int)> dfs = [&](int u) -> int {
        i64 s = 0;
        for (auto v : adj[u]) {
            s += dfs(v);
        }
        int res;
        if (s >= l[u]) {
            res = std::min<i64>(s, r[u]);
        } else {
            res = r[u];
            ans++;
        }
        
        return res;
    };
    dfs(0);
    
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

