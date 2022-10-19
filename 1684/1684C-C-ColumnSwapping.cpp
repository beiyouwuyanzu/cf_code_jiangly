// url:https://codeforces.com/contest/1684/problem/C
// time:2022-05-19 17:47:22
// name:C-ColumnSwapping

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    
    int x = 0;
    while (x < n && std::is_sorted(a[x].begin(), a[x].end())) {
        x++;
    }
    
    if (x == n) {
        std::cout << "1 1\n";
        return;
    }
    
    auto b = a[x];
    std::sort(b.begin(), b.end());
    
    std::vector<int> p;
    for (int j = 0; j < m; j++) {
        if (a[x][j] != b[j]) {
            p.push_back(j);
        }
    }
    
    if (p.size() > 2) {
        std::cout << "-1\n";
        return;
    }
    
    for (int i = 0; i < n; i++) {
        std::swap(a[i][p[0]], a[i][p[1]]);
        if (!std::is_sorted(a[i].begin(), a[i].end())) {
            std::cout << "-1\n";
            return;
        }
    }
    
    std::cout << p[0] + 1 << " " << p[1] + 1 << "\n";
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
