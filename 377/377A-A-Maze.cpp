// url:https://codeforces.com/contest/377/problem/A
// time:2021-06-19 22:50:13
// name:A-Maze

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    std::vector<int> vis(n * m);
    int start = 0;
    while (s[start / m][start % m] == '#') {
        start++;
    }
    std::vector<int> que{start};
    vis[start] = 1;
    for (int i = 0; i < int(que.size()); i++) {
        int u = que[i];
        int x = u / m, y = u % m;
        for (auto move : {std::make_pair(0, -1), {0, 1}, {-1, 0}, {1, 0}}) {
            int x0 = x + move.first;
            int y0 = y + move.second;
            if (x0 < 0 || x0 >= n || y0 < 0 || y0 >= m || s[x0][y0] == '#') {
                continue;
            }
            int v = x0 * m + y0;
            if (!vis[v]) {
                vis[v] = 1;
                que.push_back(v);
            }
        }
    }
    while (k--) {
        int u = que.back();
        s[u / m][u % m] = 'X';
        que.pop_back();
    }
    for (int i = 0; i < n; i++) {
        std::cout << s[i] << "\n";
    }
    return 0;
}
