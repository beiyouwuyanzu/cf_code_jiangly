//url:https://codeforces.com/contest/1697/problem/F
//time:2022-06-12 18:40:45
//name:F-TooManyConstraints

#include <bits/stdc++.h>

using i64 = long long;
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

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    TwoSat ts(n * 2 * k);
    for (int i = 0; i < n; i++) {
        int offset = 2 * k * i;
        for (int j = 0; j < k - 1; j++) {
            ts.addClause(offset + j, false, offset + j + 1, true);
            ts.addClause(offset + k + j, true, offset + k + j + 1, false);
            ts.addClause(offset + j, true, offset + k + j + 1, true);
            ts.addClause(offset + j, false, offset + k + j + 1, false);
        }
        ts.addClause(offset + k - 1, true, offset + k - 1, true);
        ts.addClause(offset + k, true, offset + k, true);
    }
    for (int i = 0; i < n - 1; i++) {
        int offset1 = 2 * k * i;
        int offset2 = 2 * k * (i + 1);
        for (int j = 0; j < k; j++) {
            ts.addClause(offset1 + k + j, false, offset2 + k + j, true);
        }
    }
    
    for (int i = 0; i < m; i++) {
        int t;
        std::cin >> t;
        
        if (t == 1) {
            int p, x;
            std::cin >> p >> x;
            x--;
            p--;
            
            int offset = 2 * k * p;
            
            ts.addClause(offset + x, false, offset + k + x, false);
        } else if (t == 2) {
            
            int p, q, x;
            std::cin >> p >> q >> x;
            x -= 2;
            p--;
            q--;
            
            int offset1 = 2 * k * p;
            int offset2 = 2 * k * q;
            
            if (x < k - 1) {
                ts.addClause(offset1 + x, true, offset1 + x, true);
                ts.addClause(offset2 + x, true, offset2 + x, true);
            }
            for (int j = 0; j < x; j++) {
                if (j < k && x - 1 - j < k) {
                    ts.addClause(offset1 + j, true, offset2 + x - 1 - j, true);
                }
            }
        } else {
            
            int p, q, x;
            std::cin >> p >> q >> x;
            x -= 2;
            p--;
            q--;
            
            int offset1 = 2 * k * p;
            int offset2 = 2 * k * q;
            
            if (x > k - 1) {
                ts.addClause(offset1 + k + x - (k - 1), true, offset1 + k + x - (k - 1), true);
                ts.addClause(offset2 + k + x - (k - 1), true, offset2 + k + x - (k - 1), true);
            }
            for (int j = 0; j < x + 1; j++) {
                if (j < k && x + 1 - j < k) {
                    ts.addClause(offset1 + k + j, true, offset2 + k + x + 1 - j, true);
                }
            }
        }
    }
    
    if (!ts.satisfiable()) {
        std::cout << "-1\n";
        return;
    }
    
    std::vector<int> a(n);
    
    auto ans = ts.answer();
    for (int i = 0; i < n; i++) {
        int offset = 2 * k * i;
        // for (int j = 0; j < k; j++) {
        //     std::cerr << ans[offset + j];
        // }
        // std::cerr << "\n";
        // for (int j = 0; j < k; j++) {
        //     std::cerr << ans[offset + k + j];
        // }
        // std::cerr << "\n";
        for (int j = 0; j < k; j++) {
            if (ans[offset + j] && ans[offset + k + j]) {
                a[i] = j;
            }
        }
        std::cout << a[i] + 1 << " \n"[i == n - 1];
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

