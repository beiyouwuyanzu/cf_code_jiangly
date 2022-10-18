//url:https://codeforces.com/contest/1695/problem/E
//time:2022-06-18 18:30:53
//name:E-AmbiguousDominoes

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> x(n), y(n);
    std::vector<std::vector<std::array<int, 2>>> adj(2 * n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
        x[i]--;
        y[i]--;
        adj[x[i]].push_back({ y[i], i });
        adj[y[i]].push_back({ x[i], i });
    }
    
    std::vector<bool> vise(n), vis(2 * n);
    
    std::vector<std::array<int, 2>> ans;
    std::vector<std::string> s1, s2;
    
    for (int i = 0; i < 2 * n; i++) {
        if (vis[i]) {
            continue;
        }
        std::vector<int> a;
        
        std::function<void(int)> dfs = [&](int u) {
            vis[u] = true;
            for (auto [v, i] : adj[u]) {
                if (vise[i]) {
                    continue;
                }
                vise[i] = true;
                a.push_back(v);
                if (!vis[v]) {
                    dfs(v);
                }
                a.push_back(u);
            }
        };
        dfs(i);
        
        if (a.size() == 2) {
            std::cout << "-1\n";
            return 0;
        }
        if (a.size() == 0) {
            continue;
        }
        
        int k = a.size() / 2;
        for (int i = 0; i < k; i++) {
            ans.push_back({ a[i], a[2 * k - i - 1] });
        }
        
        s1.push_back("LR");
        for (int i = 1; i < k; i += 2) {
            if (i == k - 1) {
                s1.push_back("LR");
            } else {
                s1.push_back("UU");
                s1.push_back("DD");
            }
        }
        for (int i = 0; i < k; i += 2) {
            if (i == k - 1) {
                s2.push_back("LR");
            } else {
                s2.push_back("UU");
                s2.push_back("DD");
            }
        }
    }
    
    std::cout << n << " 2\n\n";
    
    for (auto [x, y] : ans) {
        std::cout << x + 1 << " " << y + 1 << "\n";
    }
    std::cout << "\n";
    for (auto s : s1) {
        std::cout << s << "\n";
    }
    std::cout << "\n";
    for (auto s : s2) {
        std::cout << s << "\n";
    }
    
    return 0;
}

