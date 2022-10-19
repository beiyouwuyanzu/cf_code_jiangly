// url:https://codeforces.com/contest/1537/problem/F
// time:2021-06-18 18:20:30
// name:F-FigureFixing

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<int> v(n), t(n);
        for (int i = 0; i < n; i++) {
            std::cin >> v[i];
        }
        for (int i = 0; i < n; i++) {
            std::cin >> t[i];
        }
        std::vector<std::vector<int>> e(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            std::cin >> u >> v;
            u--;
            v--;
            e[u].push_back(v);
            e[v].push_back(u);
        }
        bool ok = true;
        std::vector<int> col(n, -1);
        for (int i = 0; i < n; i++) {
            if (col[i] != -1) {
                continue;
            }
            bool bipart = true;
            col[i] = 0;
            i64 sum[2] = {};
            std::queue<int> que;
            que.push(i);
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                sum[col[u]] += t[u] - v[u];
                for (auto v : e[u]) {
                    if (col[v] == -1) {
                        col[v] = !col[u];
                        que.push(v);
                    } else if (col[u] == col[v]) {
                        bipart = false;
                    }
                }
            }
            if (bipart ? sum[0] != sum[1] : (sum[0] + sum[1]) % 2 != 0) {
                ok = false;
            }
        }
        std::cout << (ok ? "YES" : "NO") << "\n";
    }
    return 0;
}

