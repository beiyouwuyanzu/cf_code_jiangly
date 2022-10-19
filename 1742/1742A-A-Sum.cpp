// url:https://codeforces.com/contest/1742/problem/A
// time:2022-10-13 17:51:34
// name:A-Sum

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int a[3];
    std::cin >> a[0] >> a[1] >> a[2];
    
    std::sort(a, a + 3);
    if (a[0] + a[1] == a[2]) {
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

