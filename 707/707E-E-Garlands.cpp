// url:https://codeforces.com/contest/707/problem/E
// time:2023-03-15 10:07:53
// name:E-Garlands

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector bulb(n, std::vector(m, std::pair(-1, -1)));
    std::vector<std::pair<int, int>> end(k);
    std::vector<std::vector<i64>> pre(k);
    
    for (int i = 0; i < k; i++) {
        int len;
        std::cin >> len;
        
        pre[i].resize(len);
        i64 sum = 0;
        for (int j = 0; j < len; j++) {
            int x, y, c;
            std::cin >> x >> y >> c;
            x--, y--;
            sum += c;
            pre[i][j] = sum;
            end[i] = {x, y};
            bulb[x][y] = {i, j};
        }
    }
    
    std::vector<bool> on(k, true);
    
    int q;
    std::cin >> q;
    while (q--) {
        std::string t;
        std::cin >> t;
        
        if (t == "SWITCH") {
            int x;
            std::cin >> x;
            x--;
            on[x] = !on[x];
        } else {
            i64 ans = 0;
            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            x1--, y1--, x2--, y2--;
            for (int i = 0; i < k; i++) {
                if (on[i] && x1 <= end[i].first && end[i].first <= x2
                        && y1 <= end[i].second && end[i].second <= y2) {
                    ans += pre[i].back();
                }
            }
            for (int i = x1; i <= x2; i++) {
                if (y1 > 0 && bulb[i][y1 - 1].first == bulb[i][y1].first
                    && bulb[i][y1].first != -1 && on[bulb[i][y1].first]) {
                    int a = bulb[i][y1].first;
                    int u = bulb[i][y1 - 1].second;
                    int v = bulb[i][y1].second;
                    if (u + 1 == v) {
                        ans -= pre[a][u];
                    }
                    if (v + 1 == u) {
                        ans += pre[a][v];
                    }
                }
                if (y2 < m - 1 && bulb[i][y2 + 1].first == bulb[i][y2].first
                    && bulb[i][y2].first != -1 && on[bulb[i][y2].first]) {
                    int a = bulb[i][y2].first;
                    int u = bulb[i][y2 + 1].second;
                    int v = bulb[i][y2].second;
                    if (u + 1 == v) {
                        ans -= pre[a][u];
                    }
                    if (v + 1 == u) {
                        ans += pre[a][v];
                    }
                }
            }
            for (int i = y1; i <= y2; i++) {
                if (x1 > 0 && bulb[x1 - 1][i].first == bulb[x1][i].first
                    && bulb[x1][i].first != -1 && on[bulb[x1][i].first]) {
                    int a = bulb[x1][i].first;
                    int u = bulb[x1 - 1][i].second;
                    int v = bulb[x1][i].second;
                    if (u + 1 == v) {
                        ans -= pre[a][u];
                    }
                    if (v + 1 == u) {
                        ans += pre[a][v];
                    }
                }
                if (x2 < n - 1 && bulb[x2 + 1][i].first == bulb[x2][i].first
                    && bulb[x2][i].first != -1 && on[bulb[x2][i].first]) {
                    int a = bulb[x2][i].first;
                    int u = bulb[x2 + 1][i].second;
                    int v = bulb[x2][i].second;
                    if (u + 1 == v) {
                        ans -= pre[a][u];
                    }
                    if (v + 1 == u) {
                        ans += pre[a][v];
                    }
                }
            }
            std::cout << ans << "\n";
        }
    }
    
    return 0;
}

