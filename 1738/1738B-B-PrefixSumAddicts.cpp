//url:https://codeforces.com/contest/1738/problem/B
//time:2022-09-30 17:46:02
//name:B-PrefixSumAddicts

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<i64> s(n + 1);
    for (int i = n - k + 1; i <= n; i++) {
        std::cin >> s[i];
    }
    
    if (k == 1) {
        std::cout << "YES\n";
        return;
    }
    
    for (int i = n - k + 1; i <= n - 2; i++) {
        if (s[i + 1] - s[i] > s[i + 2] - s[i + 1]) {
            std::cout << "NO\n";
            return;
        }
    }
    
    i64 t = s[n - k + 2] - s[n - k + 1];
    if (s[n - k + 1] - (n - k + 1) * t <= 0) {
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
