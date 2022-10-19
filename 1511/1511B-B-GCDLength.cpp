// url:https://codeforces.com/contest/1511/problem/B
// time:2022-06-27 16:31:49
// name:B-GCDLength

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int a, b, c;
    std::cin >> a >> b >> c;
    
    auto x = '1' + std::string(a - 1, '0');
    auto y = '1' + std::string(b - 1, '0');
    
    if (a > b) {
        x[a - c]++;
    } else {
        y[b - c]++;
    }
    
    std::cout << x << " " << y << "\n";
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
