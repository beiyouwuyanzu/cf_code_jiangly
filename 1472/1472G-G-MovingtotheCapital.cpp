//url:https://codeforces.com/contest/1472/problem/G
//time:2021-01-04 18:10:11
//name:G-MovingtotheCapital

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> e(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        e[u].push_back(v);
    }
    std::vector<int> d(n, -1);
    d[0] = 0;
    std::vector<int> que;
    que.push_back(0);
    for (int i = 0; i < n; i++) {
        int u = que[i];
        for (auto v : e[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + 1;
                que.push_back(v);
            }
        }
    }
    std::vector<int> f(n);
    for (int i = 0; i < n; i++) {
        f[i] = d[i];
        for (auto v : e[i]) {
            f[i] = std::min(f[i], d[v]);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        int u = que[i];
        for (auto v : e[u]) {
            if (d[v] > d[u]) {
                f[u] = std::min(f[u], f[v]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << f[i] << " \n"[i == n - 1];
    }
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
