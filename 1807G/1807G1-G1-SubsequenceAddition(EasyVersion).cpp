// url:https://codeforces.com/contest/1807/problem/G1
// time:2023-03-20 16:12:17
// name:G1-SubsequenceAddition(EasyVersion)

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i];
    }
    std::sort(c.begin(), c.end());
    
    int s = 0;
    for (int i = 0; i < n; i++) {
        if (s + (i == 0) < c[i]) {
            std::cout << "NO\n";
            return;
        }
        s += c[i];
    }
    std::cout << "YES\n";
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
