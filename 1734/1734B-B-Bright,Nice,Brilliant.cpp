//url:https://codeforces.com/contest/1734/problem/B
//time:2022-09-23 15:31:21
//name:B-Bright,Nice,Brilliant

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            std::cout << (j == 0 || j == i) << " \n"[j == i];
        }
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
