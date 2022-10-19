// url:https://codeforces.com/contest/1508/problem/E
// time:2021-04-16 19:23:07
// name:E-TreeCalendar

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
void gg() {
    std::cout << "NO\n";
    std::exit(0);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    auto a0 = a;
    std::vector<std::vector<int>> e(n);
    int U = -1, V = -1;
    std::vector<int> parent(n, -1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        parent[v] = u;
        e[u].push_back(v);
        if (a[u] < a[v] && (U == -1 || std::make_pair(a[u], a[v]) < std::make_pair(a[U], a[V]))) {
            U = u;
            V = v;
        }
    }
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++) {
        pos[a[i]] = i;
    }
    if (U == -1) {
        U = n - 1;
    } else {
        U = a[U];
    }
    std::vector<int> vis(n);
    int bot = -1;
    std::deque<int> vals;
    i64 ans = 0;
    for (int i = U; i >= 0; i--) {
        int u = pos[i];
        if (vis[u]) {
            gg();
        }
        int x = u;
        std::vector<int> path;
        while (x != -1 && !vis[x]) {
            path.push_back(x);
            x = parent[x];
        }
        if (x != -1 && vis[x] == 2) {
            gg();
        }
        while (bot != x) {
            a[bot] = vals.back();
            vis[bot] = 2;
            vals.pop_back();
            bot = parent[bot];
        }
        while (!path.empty()) {
            int v = path.back();
            vis[v] = 1;
            vals.push_back(a[v]);
            path.pop_back();
        }
        bot = u;
        x = vals.back();
        vals.pop_back();
        ans += vals.size();
        vals.push_front(x);
    }
    while (bot != -1) {
        a[bot] = vals.back();
        vals.pop_back();
        bot = parent[bot];
    }
    int cur = 0;
    for (int i = 0; i < n; i++) {
        std::sort(e[i].begin(), e[i].end(), [&](int u, int v) {
            return a[u] < a[v];
        });
    }
    std::function<void(int)> dfs1 = [&](int u) {
        if (a[u] != cur) {
            gg();
        }
        cur++;
        for (auto v : e[u]) {
            dfs1(v);
        }
    };
    dfs1(0);
    int post = 0;
    std::vector<int> dep(n);
    std::vector<int> a1(n, -1);
    i64 res = ans;
    std::function<void(int)> dfs2 = [&](int u) {
        for (auto v : e[u]) {
            dep[v] = dep[u] + 1;
            dfs2(v);
        }
        if (post < U) {
            a1[u] = post;
            res -= dep[u];
            post++;
        }
    };
    dfs2(0);
    std::function<void(int)> dfs3 = [&](int u) {
        if (a1[u] != -1) {
            return;
        }
        a1[u] = post++;
        for (auto v : e[u]) {
            dfs3(v);
        }
    };
    dfs3(0);
    if (res < 0) {
        gg();
    }
    int S = 0;
    while (res--) {
        int V = -1;
        for (auto v : e[S]) {
            if (a1[v] > a1[S] && (V == -1 || a1[v] < a1[V])) {
                V = v;
            }
        }
        if (V == -1) {
            gg();
        }
        std::swap(a1[S], a1[V]);
        S = V;
    }
    if (a1 != a0) {
        gg();
    }
    std::cout << "YES\n";
    std::cout << ans << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] + 1 << " \n"[i == n - 1];
    }
    return 0;
}
