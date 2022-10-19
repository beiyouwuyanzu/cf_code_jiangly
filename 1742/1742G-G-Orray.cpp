// url:https://codeforces.com/contest/1742/problem/G
// time:2022-10-13 18:17:25
// name:G-Orray

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> b;
    std::vector<bool> vis(n);
    
    int cur = 0;
    for (int i = 0; i < n; i++) {
        int mx = 0, k = -1;
        for (int j = 0; j < n; j++) {
            int x = a[j] & ~cur;
            if (!vis[j] && x > mx) {
                mx = x;
                k = j;
            }
        }
        if (k < 0) {
            break;
        }
        vis[k] = true;
        b.push_back(a[k]);
        cur |= a[k];
    }
    
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            b.push_back(a[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << b[i] << " \n"[i == n - 1];
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

