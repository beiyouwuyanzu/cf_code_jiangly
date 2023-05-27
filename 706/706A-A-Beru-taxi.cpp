// url:https://codeforces.com/contest/706/problem/A
// time:2023-03-14 20:43:08
// name:A-Beru-taxi

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int a, b;
    std::cin >> a >> b;
    
    int n;
    std::cin >> n;
    double ans = 1E9;
    for (int i = 0; i < n; i++) {
        int x, y, v;
        std::cin >> x >> y >> v;
        
        ans = std::min(ans, std::sqrt((x - a) * (x - a) + (y - b) * (y - b)) / v);
    }
    
    std::cout << std::fixed << std::setprecision(10);
    std::cout << ans << "\n";
    
    return 0;
}

