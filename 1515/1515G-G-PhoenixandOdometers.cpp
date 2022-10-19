// url:https://codeforces.com/contest/1515/problem/G
// time:2021-05-02 18:31:27
// name:G-PhoenixandOdometers

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> e(n);
    for (int i = 0; i < m; i++) {
        int a, b, l;
        std::cin >> a >> b >> l;
        a--;
        b--;
        e[a].emplace_back(b, l);
    }
    int timeStamp = 0;
    int countComp = 0;
    std::vector<int> dfn(n, -1), low(n), belong(n, -1);
    std::vector<int> stk;
    std::vector<i64> dep(n);
    std::vector<i64> g(n);
    std::vector<i64> gv(n);
    std::function<void(int)> dfs = [&](int u) {
        stk.push_back(u);
        dfn[u] = low[u] = timeStamp++;
        for (auto [v, l] : e[u]) {
            if (dfn[v] == -1) {
                dep[v] = dep[u] + l;
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (belong[v] == -1) {
                low[u] = std::min(low[u], dfn[v]);
                gv[u] = std::gcd(gv[u], dep[u] - dep[v] + l);
            }
        }
        if (dfn[u] == low[u]) {
            int v;
            do {
                v = stk.back();
                stk.pop_back();
                belong[v] = countComp;
            } while (v != u);
            countComp++;
        }
    };
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; i++) {
        g[belong[i]] = std::gcd(g[belong[i]], gv[i]);
    }
    int q;
    std::cin >> q;
    while (q--) {
        int v, s, t;
        std::cin >> v >> s >> t;
        v--;
        bool ans = false;
        if (s == 0) {
            ans = true;
        } else if (g[belong[v]] == 0) {
            ans = false;
        } else {
            i64 gcd = std::gcd(g[belong[v]], i64(t));
            ans = (s % gcd == 0);
        }
        if (ans) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
