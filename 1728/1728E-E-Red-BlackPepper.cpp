//url:https://codeforces.com/contest/1728/problem/E
//time:2022-09-08 18:08:30
//name:E-Red-BlackPepper

#include <bits/stdc++.h>

using i64 = long long;

std::array<int, 3> exgcd(int a, int b) {
    if (b == 0) {
        return {a, 1, 0};
    }
    auto [g, x, y] = exgcd(b, a % b);
    return {g, y, x - a / b * y};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> b[i];
        c[i] = a[i] - b[i];
    }
    
    std::vector<i64> f(n + 1);
    f[0] = std::accumulate(b.begin(), b.end(), 0LL);
    std::sort(c.begin(), c.end(), std::greater());
    for (int i = 0; i < n; i++) {
        f[i + 1] = f[i] + c[i];
    }
    
    int high = std::max_element(f.begin(), f.end()) - f.begin();
    
    int m;
    std::cin >> m;
    
    while (m--) {
        int x, y;
        std::cin >> x >> y;
        
        auto [g, a, b] = exgcd(x, y);
        assert(1LL * a * x + 1LL * b * y == g);
        
        if (n % g != 0) {
            std::cout << -1 << "\n";
            continue;
        }
        
        a = 1LL * a * (n / g) % (y / g);
        if (a < 0) {
            a += y / g;
        }
        
        if (1LL * x * a > n) {
            std::cout << -1 << "\n";
            continue;
        }
        
        i64 d = 1LL * x * y / g;
        int min = x * a;
        int max = n - (n - x * a) % d;
        
        i64 ans = std::max(f[min], f[max]);
        if (high >= min && high <= max) {
            int l = high - (high - min) % d;
            int r = high + (max - high) % d;
            ans = std::max({ans, f[l], f[r]});
        }
        std::cout << ans << "\n";
    }
    
    return 0;
}
