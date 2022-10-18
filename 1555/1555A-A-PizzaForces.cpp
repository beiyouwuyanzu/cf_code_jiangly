//url:https://codeforces.com/contest/1555/problem/A
//time:2022-06-12 10:17:59
//name:A-PizzaForces

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    i64 n;
    std::cin >> n;
    
    i64 slice = std::max(3LL, (n + 1) / 2);
    
    std::cout << 5 * slice << "\n";
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

