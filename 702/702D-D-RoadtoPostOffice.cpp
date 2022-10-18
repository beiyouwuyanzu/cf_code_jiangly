//url:https://codeforces.com/contest/702/problem/D
//time:2021-07-12 19:12:29
//name:D-RoadtoPostOffice

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    i64 d;
    int k, a, b, t;
    std::cin >> d >> k >> a >> b >> t;
    
    i64 ans = (d - 1) / k * t + d * a;
    if (k < d) {
        ans = std::min(ans, i64(k) * a + (d - k) * b);
        ans = std::min(ans, (d / k - 1) * t + d * a + d % k * (b - a));
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
