// url:https://codeforces.com/contest/598/problem/D
// time:2023-04-23 20:51:08
// name:D-IgorIntheMuseum

#include <bits/stdc++.h>

using i64 = long long;

constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    
    std::vector vis(n, std::vector(m, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (vis[i][j] == -1 && s[i][j] == '.') {
                std::vector<std::pair<int, int>> q;
                q.emplace_back(i, j);
                vis[i][j] = 0;
                int res = 0;
                
                for (int t = 0; t < q.size(); t++) {
                    auto [x, y] = q[t];
                    for (int k = 0; k < 4; k++) {
                        int nx = x + dx[k];
                        int ny = y + dy[k];
                        if (vis[nx][ny] == -1 && s[nx][ny] == '.') {
                            q.emplace_back(nx, ny);
                            vis[nx][ny] = 0;
                        }
                        if (s[nx][ny] == '*') {
                            res += 1;
                        }
                    }
                }
                
                for (auto [x, y] : q) {
                    vis[x][y] = res;
                }
            }
        }
    }
    
    while (k--) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        std::cout << vis[x][y] << "\n";
    }
    
    return 0;
}
