//url:https://codeforces.com/contest/1681/problem/B
//time:2022-05-23 17:42:14
//name:B-CardTrick

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int m;
    std::cin >> m;
    
    std::vector<int> b(m);
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }
    
    int j = 0;
    for (int i = m - 1; i >= 0; i--) {
        if (j < n - b[i]) {
            j += b[i];
        } else {
            j -= n - b[i];
        }
    }
    
    std::cout << a[j] << "\n";
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
