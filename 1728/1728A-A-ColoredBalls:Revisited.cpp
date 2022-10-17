//url:https://codeforces.com/contest/1728/problem/A
//time:2022-09-08 17:38:15
//name:A-ColoredBalls:Revisited

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::cout << std::max_element(a.begin(), a.end()) - a.begin() + 1 << "\n";
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
