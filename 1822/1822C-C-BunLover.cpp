// url:https://codeforces.com/contest/1822/problem/C
// time:2023-04-25 15:32:56
// name:C-BunLover

#include <bits/stdc++.h> 

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::cout << 1LL * n * n + n * 2 + 2 << "\n";
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
