//url:https://codeforces.com/contest/1733/problem/E
//time:2022-09-19 18:26:13
//name:E-Conveyor

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 120;

void solve() {
    i64 t;
    int x, y;
    std::cin >> t >> x >> y;
    
    if (x + y > t) {
        std::cout << "NO\n";
        return;
    }
    
    t -= x + y;
    
    i64 f[N][N] {};
    f[0][0] = t;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j + 1 < N) {
                f[i][j + 1] += (f[i][j] + 1) / 2;
            }
            if (i + 1 < N) {
                f[i + 1][j] += f[i][j] / 2;
            }
        }
    }
    
    int X = 0, Y = 0;
    while (X < N && Y < N) {
        if (X == x && Y == y) {
            std::cout << "YES\n";
            return;
        }
        if (f[X][Y] & 1) {
            X++;
        } else {
            Y++;
        }
    }
    
    std::cout << "NO\n";
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
