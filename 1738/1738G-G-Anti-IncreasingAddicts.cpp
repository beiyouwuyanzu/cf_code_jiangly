//url:https://codeforces.com/contest/1738/problem/G
//time:2022-09-30 18:53:11
//name:G-Anti-IncreasingAddicts

#include <bits/stdc++.h>

using i64 = long long;

struct Fenwick {
    int n;
    std::vector<int> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, int v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = std::max(a[i - 1], v);
        }
    }
    int sum(int x) {
        int ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans = std::max(ans, a[i - 1]);
        }
        return ans;
    }
};

void solve() {
    int n, k;
    std::cin >> n >> k;
    k--;
    
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    
    std::vector a(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == '0') {
                a[i][j] = ((i && j) ? a[i - 1][j - 1] : 0) + 1;
            }
            if (i) {
                a[i][j] = std::max(a[i][j], a[i - 1][j]);
            }
            if (j) {
                a[i][j] = std::max(a[i][j], a[i][j - 1]);
            }
        }
    }
    
    if (a[n - 1][n - 1] > k) {
        std::cout << "NO\n";
        return;
    }
    
    std::vector b(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i - j >= n - k || j - i >= n - k) {
                b[i][j] = 1;
            }
        }
    }
    
    for (int i = k - 1; i >= 0; i--) {
        int x = i;
        int y = x + n - k;
        
        while (x - y < n - k - 1) {
            if (a[x][y] == i + 1) {
                if ((y && a[x][y - 1] == i + 1) || x + 1 == n || b[x + 1][y]) {
                    y--;
                } else {
                    x++;
                }
            } else {
                if (x + 1 < n && !b[x + 1][y]) {
                    x++;
                } else {
                    y--;
                }
            }
            b[x][y] = 1;
        }
    }
    
    std::cout << "YES\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << b[i][j];
        }
        std::cout << "\n";
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
