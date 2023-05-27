// url:https://codeforces.com/contest/609/problem/D
// time:2023-04-24 08:33:04
// name:D-Gadgetsfordollarsandpounds

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, k, s;
    std::cin >> n >> m >> k >> s;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    
    std::vector<int> t(m), c(m);
    for (int i = 0; i < m; i++) {
        std::cin >> t[i] >> c[i];
    }
    
    auto mina = a, minb = b;
    
    for (int i = 1; i < n; i++) {
        mina[i] = std::min(mina[i], mina[i-1]);
        minb[i] = std::min(minb[i], minb[i-1]);
    }
    
    auto check = [&](int x) {
        std::vector<i64> d(m);
        for (int i = 0; i < m; i++) {
            d[i] = 1LL * c[i] * (t[i] == 1 ? mina[x-1] : minb[x-1]);
        }
        std::nth_element(d.begin(), d.begin() + k, d.end());
        i64 sum = std::accumulate(d.begin(), d.begin() + k, 0LL);
        return sum <= s;
    };
    
    int lo = 1, hi = n+1;
    while (lo < hi) {
        int x = (lo + hi) / 2;
        if (check(x)) {
            hi = x;
        } else {
            lo = x+1;
        }
    }
    
    if (lo == n+1) {
        std::cout << -1 << "\n";
        return 0;
    }
    
    std::vector<i64> d(m);
    for (int i = 0; i < m; i++) {
        d[i] = 1LL * c[i] * (t[i] == 1 ? mina[lo-1] : minb[lo-1]);
    }
    std::vector<int> o(m);
    std::iota(o.begin(), o.end(), 0);
    std::nth_element(o.begin(), o.begin() + k, o.end(), [&](int i, int j) {
        return d[i] < d[j];
    });
    
    int daya = std::min_element(a.begin(), a.begin() + lo) - a.begin() + 1;
    int dayb = std::min_element(b.begin(), b.begin() + lo) - b.begin() + 1;
    
    std::cout << lo << "\n";
    for (int i = 0; i < k; i++) {
        std::cout << o[i]+1 << " " << (t[o[i]] == 1 ? daya : dayb) << "\n";
    }
    
    return 0;
}
