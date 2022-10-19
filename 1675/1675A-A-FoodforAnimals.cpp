// url:https://codeforces.com/contest/1675/problem/A
// time:2022-05-05 17:36:18
// name:A-FoodforAnimals

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int a, b, c, x, y;
    std::cin >> a >> b >> c >> x >> y;
    
    if (a + c >= x && b + c >= y && a + b + c >= x + y) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
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
