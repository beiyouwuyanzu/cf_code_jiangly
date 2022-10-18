//url:https://codeforces.com/contest/702/problem/C
//time:2021-07-12 19:05:32
//name:C-CellularNetwork

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }
    
    int ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j < m && b[j] < a[i]) {
            j++;
        }
        int v = 2e9;
        if (j < m) {
            v = std::min(v, std::abs(a[i] - b[j]));
        }
        if (j > 0) {
            v = std::min(v, std::abs(a[i] - b[j - 1]));
        }
        ans = std::max(ans, v);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
