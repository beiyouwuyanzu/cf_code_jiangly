// url:https://codeforces.com/contest/843/problem/D
// time:2021-04-19 12:42:00
// name:D-DynamicShortestPath

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
constexpr int N = 100000;
std::queue<int> que[N];
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::vector<int>> e(n);
    std::vector<int> c(m), to(m + 1);
    for (int i = 0; i < m; i++) {
        int u;
        std::cin >> u >> to[i] >> c[i];
        u--;
        to[i]--;
        e[u].push_back(i);
    }
    std::vector<i64> dis(n, -1);
    std::priority_queue<std::pair<i64, int>> h;
    h.emplace(0, 0);
    while (!h.empty()) {
        auto [d, u] = h.top();
        h.pop();
        if (dis[u] != -1) {
            continue;
        }
        d = -d;
        dis[u] = d;
        for (auto i : e[u]) {
            h.emplace(-d - c[i], to[i]);
        }
    }
    while (q--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int v;
            std::cin >> v;
            v--;
            std::cout << dis[v] << "\n";
        } else {
            int k;
            std::cin >> k;
            for (int i = 0; i < k; i++) {
                int j;
                std::cin >> j;
                j--;
                c[j]++;
            }
            que[0].push(0);
            std::vector<int> h(n, -1);
            for (int i = 0; i < n; i++) {
                while (!que[i].empty()) {
                    int u = que[i].front();
                    que[i].pop();
                    if (h[u] != -1) {
                        continue;
                    }
                    h[u] = i;
                    for (auto j : e[u]) {
                        i64 d = i + c[j] + dis[u] - dis[to[j]];
                        if (h[to[j]] == -1 && d < n) {
                            que[d].push(to[j]);
                        }
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                if (h[i] != -1) {
                    dis[i] += h[i];
                }
            }
        }
    }
    return 0;
}
