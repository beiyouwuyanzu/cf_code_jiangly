// url:https://codeforces.com/contest/600/problem/F
// time:2023-04-24 07:22:06
// name:F-Edgecoloringofbipartitegraph

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int a, b, m;
    std::cin >> a >> b >> m;
    
    std::vector<std::vector<std::pair<int, int>>> adj(a+b);
    std::vector<int> x(m), y(m);
    for (int i = 0; i < m; i++) {
        std::cin >> x[i] >> y[i];
        x[i]--, y[i]--;
        y[i] += a;
        adj[x[i]].emplace_back(y[i], i);
        adj[y[i]].emplace_back(x[i], i);
    }
    
    int d = 0;
    for (int i = 0; i < a+b; i++) {
        d = std::max(d, int(adj[i].size()));
    }
    
    std::vector f(a+b, std::vector(d, -1));
    std::vector c(m, -1);
    
    for (int i = 0; i < m; i++) {
        std::vector<int> cx, cy;
        for (int k = 0; k < d; k++) {
            if (f[x[i]][k] != -1 && f[y[i]][k] == -1) {
                cx.push_back(k);
            }
            if (f[x[i]][k] == -1 && f[y[i]][k] != -1) {
                cy.push_back(k);
            }
        }
        for (int j = 0; j < std::min(cx.size(), cy.size()); j++) {
            int u = cx[j], v = cy[j];
            int t = x[i];
            std::vector<int> e;
            while (f[t][u] != -1) {
                assert(0 <= t && t < a+b);
                assert(0 <= u && u < d);
                int k = f[t][u];
                e.push_back(k);
                f[x[k]][u] = f[y[k]][u] = -1;
                std::swap(u, v);
                t = x[k] ^ y[k] ^ t;
            }
            for (auto k : e) {
                c[k] ^= u ^ v;
                f[x[k]][c[k]] = f[y[k]][c[k]] = k;
            }
        }
        for (int k = 0; k < d; k++) {
            if (f[x[i]][k] == -1 && f[y[i]][k] == -1) {
                c[i] = k;
                f[x[i]][k] = f[y[i]][k] = i;
                break;
            }
        }
    }
    
    std::cout << d << "\n";
    for (int i = 0; i < m; i++) {
        std::cout << c[i]+1 << " \n"[i == m-1];
    }
    
    return 0;
}
