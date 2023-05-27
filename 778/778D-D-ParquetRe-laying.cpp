// url:https://codeforces.com/contest/778/problem/D
// time:2023-04-22 21:11:08
// name:D-ParquetRe-laying

#include <bits/stdc++.h>

using i64 = long long;

constexpr int dx[] = {-1, 1, 0, 0};
constexpr int dy[] = {0, 0, -1, 1};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::string> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    
    std::vector f(n+1, std::vector(m+1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            f[i][j] = f[i-1][j] ^ (a[i-1][j-1] == 'L') ^ (b[i-1][j-1] == 'L');
        }
    }
    
    std::vector dis(n+1, std::vector(m+1, -1));
    std::deque<std::tuple<int, int, int>> q;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0 || i == n || j == m) {
                q.emplace_back(i, j, 0);
            }
        }
    }
    
    auto valid = [&](int x, int y) {
        return 0 <= x && x <= n && 0 <= y && y <= m;
    };
    
    while (!q.empty()) {
        auto [x, y, d] = q.front();
        q.pop_front();
        
        if (dis[x][y] != -1) {
            continue;
        }
        dis[x][y] = d;
        
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (valid(nx, ny)) {
                if (f[nx][ny] == f[x][y]) {
                    q.emplace_front(nx, ny, d);
                } else {
                    q.emplace_back(nx, ny, d+1);
                }
            }
        }
    }
    
    std::vector<std::pair<int, int>> ansl, ansr;
    
    while (true) {
        int max = 0;
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                max = std::max(max, dis[i][j]);
            }
        }
        if (!max) {
            break;
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (dis[i][j] == max) {
                    bool adj = false;
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if (valid(nx, ny) && dis[nx][ny] == max-1) {
                            adj = true;
                        }
                    }
                    if (!adj) {
                        continue;
                    }
                    if (a[i-1][j-1] == 'L' && a[i-1][j] == 'R' && a[i][j-1] == 'L' && a[i][j] == 'R') {
                        a[i-1][j-1] = 'U';
                        a[i-1][j] = 'U';
                        a[i][j-1] = 'D';
                        a[i][j] = 'D';
                        dis[i][j] -= 1;
                        ansl.emplace_back(i, j);
                    } else if (b[i-1][j-1] == 'L' && b[i-1][j] == 'R' && b[i][j-1] == 'L' && b[i][j] == 'R') {
                        b[i-1][j-1] = 'U';
                        b[i-1][j] = 'U';
                        b[i][j-1] = 'D';
                        b[i][j] = 'D';
                        dis[i][j] -= 1;
                        ansr.emplace_back(i, j);
                    } else if (a[i-1][j-1] == 'U' && a[i-1][j] == 'U' && a[i][j-1] == 'D' && a[i][j] == 'D') {
                        a[i-1][j-1] = 'L';
                        a[i-1][j] = 'R';
                        a[i][j-1] = 'L';
                        a[i][j] = 'R';
                        dis[i][j] -= 1;
                        ansl.emplace_back(i, j);
                    } else if (b[i-1][j-1] == 'U' && b[i-1][j] == 'U' && b[i][j-1] == 'D' && b[i][j] == 'D') {
                        b[i-1][j-1] = 'L';
                        b[i-1][j] = 'R';
                        b[i][j-1] = 'L';
                        b[i][j] = 'R';
                        dis[i][j] -= 1;
                        ansr.emplace_back(i, j);
                    }
                }
            }
        }
        // for (int i = 0; i < n; i++) {
        //     std::cerr << a[i] << "\n";
        // }
        // std::cerr << "\n";
        // for (int i = 0; i < n; i++) {
        //     std::cerr << b[i] << "\n";
        // }
        // std::cerr << "\n";
        // for (int i = 0; i <= n; i++) {
        //     for (int j = 0; j <= m; j++) {
        //         std::cerr << dis[i][j];
        //     }
        //     std::cerr << "\n";
        // }
        // std::cerr << "\n";
    }
    
    ansl.insert(ansl.end(), ansr.rbegin(), ansr.rend());
    std::cout << ansl.size() << "\n";
    for (auto [x, y] : ansl) {
        std::cout << x << " " << y << "\n";
    }
    
    return 0;
}
