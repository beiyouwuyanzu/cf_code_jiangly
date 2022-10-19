// url:https://codeforces.com/contest/1676/problem/G
// time:2022-05-10 17:58:40
// name:G-White-BlackBalancedSubtrees

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> s(n), p(n);
    p[0] = -1;
    for (int i = 1; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
    }
    for (int i = 0; i < n; i++) {
        char c;
        std::cin >> c;
        s[i] = c == 'W' ? 1 : -1;
    }
    for (int i = n - 1; i > 0; i--) {
        s[p[i]] += s[i];
    }
    std::cout << std::count(s.begin(), s.end(), 0) << "\n";
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
