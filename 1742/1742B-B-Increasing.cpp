// url:https://codeforces.com/contest/1742/problem/B
// time:2022-10-13 17:52:53
// name:B-Increasing

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::set<int> s;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        s.insert(x);
    }
    if (int(s.size()) == n) {
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

