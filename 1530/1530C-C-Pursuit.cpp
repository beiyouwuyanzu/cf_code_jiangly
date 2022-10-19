// url:https://codeforces.com/contest/1530/problem/C
// time:2021-07-17 17:47:14
// name:C-Pursuit

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        
        std::vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            std::cin >> b[i];
        }
        std::sort(a.begin(), a.end(), std::greater<>());
        std::sort(b.begin(), b.end(), std::greater<>());
        
        std::vector<i64> sa(n + 1), sb(n + 1);
        for (int i = 0; i < n; i++) {
            sa[i + 1] = sa[i] + a[i];
            sb[i + 1] = sb[i] + b[i];
        }
        
        int lo = 0, hi = 1e7;
        while (lo < hi) {
            int k = (lo + hi) / 2;
            
            int m = (n + k) - (n + k) / 4;
            int ca, cb;
            if (m <= k) {
                ca = 100 * m;
            } else {
                ca = 100 * k + sa[m - k];
            }
            cb = sb[std::min(n, m)];
            
            if (ca >= cb) {
                hi = k;
            } else {
                lo = k + 1;
            }
        }
        
        std::cout << lo << "\n";
    }
    
    return 0;
}
