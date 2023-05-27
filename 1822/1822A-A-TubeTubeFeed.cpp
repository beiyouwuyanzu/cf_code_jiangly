// url:https://codeforces.com/contest/1822/problem/A
// time:2023-04-25 15:32:26
// name:A-TubeTubeFeed

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, t;
    std::cin >> n >> t;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    
    int x = -2;
    for (int i = 0; i < n; i++) {
        if (a[i] + i <= t) {
            if (x ==  -2 || b[x] < b[i]) {
                x = i;
            }
        }
    }
    std::cout << x+1 << "\n";
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
