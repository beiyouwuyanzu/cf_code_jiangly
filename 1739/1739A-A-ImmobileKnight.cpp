//url:https://codeforces.com/contest/1739/problem/A
//time:2022-09-29 17:53:22
//name:A-ImmobileKnight

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    if (n == 1 || m == 1) {
        std::cout << 1 << " " << 1 << "\n";
    } else {
        std::cout << 2 << " " << 2 << "\n";
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
