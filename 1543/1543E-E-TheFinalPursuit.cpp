// url:https://codeforces.com/contest/1543/problem/E
// time:2021-07-07 19:02:41
// name:E-TheFinalPursuit

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        int N = 1 << n;
        
        std::vector<std::vector<int>> e(N);
        for (int i = 0; i < N * n / 2; i++) {
            int u, v;
            std::cin >> u >> v;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        
        std::vector<int> vis(N);
        
        auto solve = [&](auto self, auto a) -> std::vector<int> {
            if (a.size() == 1) {
                return a;
            }
            
            int w = vis[a[0]];
            
            int u = a[0];
            int v;
            for (auto x : e[u]) {
                if (vis[x] == w) {
                    v = x;
                    break;
                }
            }
            
            vis[u] = w + 2;
            vis[v] = w + 1;
            
            std::queue<int> que;
            que.push(u);
            que.push(v);
            
            std::vector<int> b;
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                if (vis[u] == w + 2) {
                    b.push_back(u);
                }
                for (auto v : e[u]) {
                    if (vis[v] == w) {
                        vis[v] = vis[u];
                        que.push(v);
                    }
                }
            }
            
            b = self(self, b);
            int m = b.size();
            for (int i = 0; i < m; i++) {
                for (auto v : e[b[i]]) {
                    if (vis[v] == w + 1) {
                        b.push_back(v);
                    }
                }
            }
            
            return b;
        };
        
        std::vector<int> p(N);
        std::iota(p.begin(), p.end(), 0);
        p = solve(solve, p);
        
        for (int i = 0; i < N; i++) {
            std::cout << p[i] << " \n"[i == N - 1];
        }
        
        if (N % n != 0) {
            std::cout << "-1\n";
            continue;
        }
        
        std::vector<int> a(N);
        for (int i = 1; i < N; i++) {
            int u = __builtin_ctz(i);
            a[p[i]] = a[p[i & (i - 1)]] ^ u;
        }
        
        for (int i = 0; i < N; i++) {
            std::cout << a[i] << " \n"[i == N - 1];
        }
    }
    
    return 0;
}
