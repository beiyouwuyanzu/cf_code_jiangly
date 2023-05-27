// url:https://codeforces.com/contest/331/problem/E1
// time:2023-04-27 08:45:07
// name:E1-DejaVu

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector e(n, std::vector(n, false));
    std::vector v(n, std::vector(n, std::vector<int>()));
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        e[x][y] = true;
        int k;
        std::cin >> k;
        v[x][y].resize(k);
        for (int j = 0; j < k; j++) {
            std::cin >> v[x][y][j];
            v[x][y][j]--;
        }
    }
    
    std::vector<std::tuple<int, int, int, std::vector<int>>> f[2][2];
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (e[x][y]) {
                for (int i = 0; i <= v[x][y].size(); i++) {
                    if ((!i || v[x][y][i-1] == x) && (i == v[x][y].size() || v[x][y][i] == y)) {
                        std::vector<int> l, r;
                        l.assign(v[x][y].rend() - i, v[x][y].rend());
                        if (!l.empty()) {
                            bool ok = true;
                            for (int j = 0; j+1 < l.size() && l.size() <= 2*n+1; j++) {
                                if (!e[l[j+1]][l[j]]) {
                                    ok = false;
                                    break;
                                }
                                auto &f = v[l[j+1]][l[j]];
                                l.insert(l.end(), f.rbegin(), f.rend());
                            }
                            if (!ok || l.size() > 2*n+1) {
                                break;
                            }
                        }
                        
                        r.assign(v[x][y].begin() + i, v[x][y].end());
                        if (!r.empty()) {
                            bool ok = true;
                            for (int j = 0; j+1 < r.size() && r.size() <= 2*n+1; j++) {
                                if (!e[r[j]][r[j+1]]) {
                                    ok = false;
                                    break;
                                }
                                auto &f = v[r[j]][r[j+1]];
                                r.insert(r.end(), f.begin(), f.end());
                            }
                            if (!ok || r.size() > 2*n+1) {
                                break;
                            }
                        }
                        
                        std::vector<int> a;
                        a.insert(a.end(), l.rbegin(), l.rend());
                        a.insert(a.end(), r.begin(), r.end());
                        
                        f[!l.empty()][!r.empty()].emplace_back(l.empty() ? x : l.back(), r.empty() ? y : r.back(), l.size() + r.size(), a);
                    }
                }
            }
        }
    }
    
    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         for (auto [x, y, l] : f[i][j]) {
    //             std::cerr << i << " " << j << " " << x+1 << " " << y+1 << " " << l << "\n";
    //         }
    //     }
    // }
    
    std::vector dp(2*n+2, std::vector(n, std::array<std::tuple<int, int, std::vector<int>>, 2>{}));
    for (int i = 0; i <= 2*n+1; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j].fill({-1, -1, {}});
        }
    }
    for (int i = 0; i < n; i++) {
        dp[0][i][0] = {};
    }
    for (int i = 0; i <= 2*n+1; i++) {
        for (int u = 0; u < 2; u++) {
            for (int v = 0; v < 2; v++) {
                for (auto [x, y, l, t] : f[u][v]) {
                    if (i+l <= 2*n+1 && std::get<0>(dp[i][x][!u]) != -1) {
                        dp[i+l][y][v] = {x, !u, t};
                    }
                }
            }
        }
    }
    for (int i = 1; i <= 2*n; i++) {
        for (int x = 0; x < n; x++) {
            if (std::get<0>(dp[i][x][1]) != -1) {
                std::vector<int> ans;
                int v = x, t = 1, len = i;
                while (len) {
                    auto [u, q, a] = dp[len][v][t];
                    ans.insert(ans.begin(), a.begin(), a.end());
                    len -= a.size();
                    v = u;
                    t = q;
                }
                std::cout << ans.size() << "\n";
                for (int i = 0; i < ans.size(); i++) {
                    std::cout << ans[i]+1 << " \n"[i == ans.size()-1];
                }
                return 0;
            }
        }
    }
    std::cout << 0 << "\n";
    
    return 0;
}
