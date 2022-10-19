// url:https://codeforces.com/contest/1520/problem/G
// time:2021-05-05 18:23:12
// name:G-ToGoOrNotToGo?

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr i64 inf = 1e18;
const std::vector<std::pair<int, int>> moves{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, w;
    std::cin >> n >> m >> w;
    std::vector<std::vector<int>> a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    std::vector<int> dis(n * m, -1);
    auto bfs = [&](int sx, int sy) {
        dis.assign(n * m, -1);
        std::queue<int> que;
        que.push(sx * m + sy);
        dis[sx * m + sy] = 0;
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            int x = u / m, y = u % m;
            for (auto [dx, dy] : moves) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m || a[nx][ny] < 0) {
                    continue;
                }
                int v = nx * m + ny;
                if (dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    que.push(v);
                }
            }
        }
    };
    bfs(0, 0);
    i64 ans = inf;
    if (dis[n * m - 1] >= 0) {
        ans = i64(dis[n * m - 1]) * w;
    }
    i64 smin = inf, tmin = inf;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] > 0 && dis[i * m + j] >= 0) {
                smin = std::min(smin, i64(dis[i * m + j]) * w + a[i][j]);
            }
        }
    }
    bfs(n - 1, m - 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] > 0 && dis[i * m + j] >= 0) {
                tmin = std::min(tmin, i64(dis[i * m + j]) * w + a[i][j]);
            }
        }
    }
    ans = std::min(smin + tmin, ans);
    if (ans >= inf) {
        ans = -1;
    }
    std::cout << ans << "\n";
    return 0;
}
