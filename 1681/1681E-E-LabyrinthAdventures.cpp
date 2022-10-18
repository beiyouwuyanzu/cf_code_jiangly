//url:https://codeforces.com/contest/1681/problem/E
//time:2022-05-23 19:06:25
//name:E-LabyrinthAdventures

#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::map<std::array<int, 2>, int> index;
    int N = 0;
    std::vector<int> x1(n - 1), y1(n - 1), x2(n - 1), y2(n - 1);
    
    std::vector<std::array<int, 2>> coor;
    std::vector<std::vector<int>> layer(n);
    std::vector<int> lay;
    auto add = [&](int x, int y) {
        if (!index.contains({x, y})) {
            lay.push_back(std::max(x, y));
            layer[std::max(x, y)].push_back(N);
            coor.push_back({x, y});
            index[{x, y}] = N++;
        }
    };
    
    for (int i = 0; i < n - 1; i++) {
        std::cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        x1[i]--;
        y1[i]--;
        x2[i]--;
        y2[i]--;
        
        add(x1[i], y1[i]);
        add(x1[i] + 1, y1[i]);
        add(x2[i], y2[i]);
        add(x2[i], y2[i] + 1);
    }
    
    std::vector<std::vector<std::array<int, 2>>> adj(N);
    
    auto addEdge = [&](int u, int v) {
        int d = std::abs(coor[u][0] - coor[v][0]) + std::abs(coor[u][1] - coor[v][1]);
        adj[u].push_back({v, d});
        adj[v].push_back({u, d});
    };
    for (int i = 0; i < n - 1; i++) {
        addEdge(index[{x1[i], y1[i]}], index[{x1[i] + 1, y1[i]}]);
        addEdge(index[{x2[i], y2[i]}], index[{x2[i], y2[i] + 1}]);
    }
    for (int i = 0; i < n; i++) {
        for (auto u : layer[i]) {
            for (auto v : layer[i]) {
                if (u == v) {
                    break;
                }
                addEdge(u, v);
            }
        }
    }
    
    int q;
    std::cin >> q;
    std::vector<i64> ans(q, inf);
    x1.resize(q);
    y1.resize(q);
    x2.resize(q);
    y2.resize(q);
    std::vector<int> l1(q), l2(q);
    
    for (int i = 0; i < q; i++) {
        std::cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        x1[i]--;
        y1[i]--;
        x2[i]--;
        y2[i]--;
        
        l1[i] = std::max(x1[i], y1[i]);
        l2[i] = std::max(x2[i], y2[i]);
        
        if (l1[i] > l2[i]) {
            std::swap(x1[i], x2[i]);
            std::swap(y1[i], y2[i]);
            std::swap(l1[i], l2[i]);
        }
        if (l1[i] == l2[i]) {
            ans[i] = std::abs(x1[i] - x2[i]) + std::abs(y1[i] - y2[i]);
        }
    }
    
    std::vector<i64> dis(N, -1);
    std::function<void(int, int, std::vector<int>)> solve = [&](int l, int r, std::vector<int> qs) {
        if (l > r || qs.empty()) {
            return;
        }
        int m = (l + r) / 2;
        for (auto s : layer[m]) {
            for (int i = l; i <= r; i++) {
                for (auto x : layer[i]) {
                    dis[x] = -1;
                }
            }
            
            std::priority_queue<std::pair<i64, int>, std::vector<std::pair<i64, int>>, std::greater<>> h;
            h.emplace(0, s);
            while (!h.empty()) {
                auto [d, x] = h.top();
                h.pop();
                if (dis[x] != -1) {
                    continue;
                }
                dis[x] = d;
                for (auto [v, c] : adj[x]) {
                    if (l <= lay[v] && lay[v] <= r) {
                        h.emplace(d + c, v);
                    }
                }
            }
            
            for (auto j : qs) {
                i64 d1 = inf;
                i64 d2 = inf;
                for (auto u : layer[l1[j]]) {
                    d1 = std::min(d1, dis[u] + std::abs(x1[j] - coor[u][0]) + std::abs(y1[j] - coor[u][1]));
                }
                for (auto u : layer[l2[j]]) {
                    d2 = std::min(d2, dis[u] + std::abs(x2[j] - coor[u][0]) + std::abs(y2[j] - coor[u][1]));
                }
                ans[j] = std::min(ans[j], d1 + d2);
            }
        }
        
        std::vector<int> ql, qr;
        for (auto j : qs) {
            if (l2[j] < m) {
                ql.push_back(j);
            }
            if (l1[j] > m) {
                qr.push_back(j);
            }
        }
        solve(l, m - 1, ql);
        solve(m + 1, r, qr);
    };
    std::vector<int> p(q);
    std::iota(p.begin(), p.end(), 0);
    solve(0, n - 1, p);
    
    for (auto x : ans) {
        std::cout << x << "\n";
    }
    
    return 0;
}
