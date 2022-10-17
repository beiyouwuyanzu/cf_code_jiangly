//url:https://codeforces.com/contest/1719/problem/A
//time:2022-09-29 14:33:55
//name:A-ChipGame

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    if ((n + m) % 2 == 0) {
        std::cout << "Tonya\n";
    } else {
        std::cout << "Burenka\n";
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
