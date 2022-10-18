//url:https://codeforces.com/contest/641/problem/F
//time:2021-07-09 22:29:47
//name:F-LittleArtemand2-SAT

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2000;

struct TwoSat {
    int n;
    std::vector<std::vector<int>> e;
    std::vector<bool> ans;
    TwoSat(int n) : n(n), e(2 * n), ans(n) {}
    void addClause(int u, bool f, int v, bool g) {
        e[2 * u + !f].push_back(2 * v + g);
        e[2 * v + !g].push_back(2 * u + f);
    }
    bool satisfiable() {
        std::vector<int> id(2 * n, -1), dfn(2 * n, -1), low(2 * n, -1);
        std::vector<int> stk;
        int now = 0, cnt = 0;
        std::function<void(int)> tarjan = [&](int u) {
            stk.push_back(u);
            dfn[u] = low[u] = now++;
            for (auto v : e[u]) {
                if (dfn[v] == -1) {
                    tarjan(v);
                    low[u] = std::min(low[u], low[v]);
                } else if (id[v] == -1) {
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
            if (dfn[u] == low[u]) {
                int v;
                do {
                    v = stk.back();
                    stk.pop_back();
                    id[v] = cnt;
                } while (v != u);
                ++cnt;
            }
        };
        for (int i = 0; i < 2 * n; ++i) if (dfn[i] == -1) tarjan(i);
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            ans[i] = id[2 * i] > id[2 * i + 1];
        }
        return true;
    }
    std::vector<bool> answer() { return ans; }
};

void solve(int n, std::vector<std::pair<int, int>> a, std::vector<std::pair<int, int>> b) {
    std::vector<std::bitset<N>> t(2 * n), tt(2 * n);
    
    for (auto [u, v] : a) {
        bool f = u > 0, g = v > 0;
        u = std::abs(u) - 1;
        v = std::abs(v) - 1;
        t[u + !f * n][v + g * n] = 1;
        t[v + !g * n][u + f * n] = 1;
    }
    
    for (int i = 0; i < 2 * n; i++) {
        t[i][i] = 1;
    }
    
    for (int k = 0; k < 2 * n; k++) {
        for (int i = 0; i < 2 * n; i++) {
            if (t[i][k]) {
                t[i] |= t[k];
            }
        }
    }
    
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n; j++) {
            tt[i][j] = t[j][i];
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (t[i][i + n] && t[i + n][i]) {
            return;
        }
    }
    
    for (auto [u, v] : b) {
        if (u == -v) {
            continue;
        }
        
        bool f = u > 0, g = v > 0;
        u = std::abs(u) - 1;
        v = std::abs(v) - 1;
        
        int u1 = u + f * n, u2 = u + !f * n;
        int v1 = v + g * n, v2 = v + !g * n;
        
        if (t[u2][u1]) {
            continue;
        }
        if (t[v2][v1]) {
            continue;
        }
        
        auto h = (t[u2] & tt[v1]) | (t[v2] & tt[u1]);
        
        if ((h & (h >> n)).any()) {
            continue;
        }
        
        TwoSat ts(n);
        
        ts.addClause(u, !f, u, !f);
        ts.addClause(v, !g, v, !g);
        
        for (auto [u, v] : a) {
            bool f = u > 0, g = v > 0;
            u = std::abs(u) - 1;
            v = std::abs(v) - 1;
            
            ts.addClause(u, f, v, g);
        }
        
        assert(ts.satisfiable());
        auto ans = ts.answer();
        
        for (int i = 0; i < n; i++) {
            std::cout << ans[i] << " \n"[i == n - 1];
        }
        
        std::exit(0);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m1, m2;
    std::cin >> n >> m1 >> m2;
    
    std::vector<std::pair<int, int>> a(m1), b(m2);
    for (int i = 0; i < m1; i++) {
        std::cin >> a[i].first >> a[i].second;
    }
    for (int i = 0; i < m2; i++) {
        std::cin >> b[i].first >> b[i].second;
    }
    
    solve(n, a, b);
    solve(n, b, a);
    
    std::cout << "SIMILAR\n";
    
    return 0;
}
