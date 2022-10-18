//url:https://codeforces.com/contest/1695/problem/A
//time:2022-06-18 17:42:37
//name:A-SubrectangleGuess

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::vector<int>(m));
    
    int max = std::numeric_limits<int>::min();
    int x = -1;
    int y = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
            if (a[i][j] > max) {
                max = a[i][j];
                x = i;
                y = j;
            }
        }
    }
    
    int h = std::max(x + 1, n - x);
    int w = std::max(y + 1, m - y);
    
    std::cout << h * w << "\n";
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

