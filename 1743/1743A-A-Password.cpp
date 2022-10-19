// url:https://codeforces.com/contest/1743/problem/A
// time:2022-10-17 17:46:39
// name:A-Password

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
    }
    
    std::cout << (10 - n) * (9 - n) * 3 << "\n";
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
