// url:https://codeforces.com/contest/1675/problem/C
// time:2022-05-05 17:41:02
// name:C-DetectiveTask

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int ans = 0;
    std::string s;
    std::cin >> s;
    
    int n = s.length();
    
    int zero = 0;
    while (zero < n && s[zero] != '0') {
        zero++;
    }
    
    int one = n - 1;
    while (one >= 0 && s[one] != '1') {
        one--;
    }
    
    for (int i = 0; i < n; i++) {
        if (zero >= i && one <= i) {
            ans++;
        }
    }
    
    std::cout << ans << "\n";
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
