// url:https://codeforces.com/contest/1684/problem/F
// time:2022-05-19 18:30:13
// name:F-DiverseSegments

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> R(n);
    for (int i = 0; i < n; i++) {
        R[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        r--;
        R[l] = std::max(R[l], r);
    }
    for (int i = 1; i < n; i++) {
        R[i] = std::max(R[i], R[i - 1]);
    }
    
    int maxL = n - 1, minR = 0;
    
    std::vector<int> f(n);
    for (int i = 0; i < n; i++) {
        f[i] = i;
    }
    
    bool nice = true;
    
    std::map<int, std::vector<int>> p;
    for (int i = 0; i < n; i++) {
        p[a[i]].push_back(i);
    }
    
    for (auto [x, p] : p) {
        int m = p.size();
        for (int i = 0; i + 1 < m; i++) {
            int u = p[i], v = p[i + 1];
            if (R[u] >= v) {
                maxL = std::min(maxL, v);
                minR = std::max(minR, u);
                nice = false;
            }
        }
        for (int i = 0, j = 0; i < m; i++) {
            while (j + 1 < m && p[j + 1] <= R[p[i]]) {
                j++;
            }
            if (i < j) {
                int u = p[i], v = p[j];
                f[u + 1] = std::max(f[u + 1], v);
            }
        }
    }
    
    for (int i = 1; i < n; i++) {
        f[i] = std::max(f[i - 1], f[i]);
    }
    
    if (nice) {
        std::cout << "0\n";
        return;
    }
    
    int ans = n;
    for (int l = 0; l <= maxL; l++) {
        ans = std::min(ans, std::max(minR, f[l]) - l + 1);
    }
    
    std::cout << ans << "\n";
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
