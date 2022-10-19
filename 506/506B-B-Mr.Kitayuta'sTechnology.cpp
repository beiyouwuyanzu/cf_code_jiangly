// url:https://codeforces.com/contest/506/problem/B
// time:2021-06-24 16:50:17
// name:B-Mr.Kitayuta'sTechnology

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> e(n);
    std::vector<std::vector<int>> e1(n);
    std::vector<int> deg(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        e[u].push_back(v);
        deg[v]++;
        e1[u].push_back(v);
        e1[v].push_back(u);
    }
    int ans = n;
    std::vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        std::queue<int> que, que2;
        que.push(i);
        vis[i] = true;
        int cnt = 0;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            if (deg[u] == 0) {
                que2.push(u);
            }
            cnt++;
            for (auto v : e1[u]) {
                if (!vis[v]) {
                    que.push(v);
                    vis[v] = true;
                }
            }
        }
        while (!que2.empty()) {
            int u = que2.front();
            cnt--;
            que2.pop();
            for (auto v : e[u]) {
                if (--deg[v] == 0) {
                    que2.push(v);
                }
            }
        }
        if (cnt == 0) {
            ans--;
        }
    }
    std::cout << ans << "\n";
    return 0;
}
