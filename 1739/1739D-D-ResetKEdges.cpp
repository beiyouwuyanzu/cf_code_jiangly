//url:https://codeforces.com/contest/1739/problem/D
//time:2022-09-29 18:12:03
//name:D-ResetKEdges

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> p(n);
    for (int i = 1; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
    }
    
    int lo = 0, hi = n - 1;
    while (hi - lo > 1) {
        int x = (lo + hi) / 2;
        
        int steps = 0;
        std::vector<int> h(n);
        for (int i = n - 1; i > 0; i--) {
            if (h[i] == x - 1 && p[i] != 0) {
                steps++;
            } else {
                h[p[i]] = std::max(h[p[i]], h[i] + 1);
            }
        }
        
        if (steps <= k) {
            hi = x;
        } else {
            lo = x;
        }
    }
    
    std::cout << hi << "\n";
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
