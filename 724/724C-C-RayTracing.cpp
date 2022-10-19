// url:https://codeforces.com/contest/724/problem/C
// time:2021-12-23 17:26:18
// name:C-RayTracing

#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1E18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, k;
    std::cin >> n >> m >> k;
    
    int g = 2 * std::gcd(n, m);
    i64 l = 1LL * (2 * n) / g * (2 * m);
    
    i64 v = 0;
    while ((v - g) % (2 * m) != 0) {
        v += 2 * n;
    }
    
    auto work = [&](int x, int y) {
        if ((y - x) % g != 0) {
            return inf;
        }
        
        i64 t = x + (y - x) / g * v;
        t = (t % l + l) % l;
        return t;
    };
    
    while (k--) {
        int x, y;
        std::cin >> x >> y;
        
        i64 ans = std::min({work(x, y), work(2 * n - x, y), work(x, 2 * m - y), work(2 * n - x, 2 * m - y)});
        
        if (ans == inf) {
            ans = -1;
        }
        std::cout << ans << "\n";
    }
    
    return 0;
}
