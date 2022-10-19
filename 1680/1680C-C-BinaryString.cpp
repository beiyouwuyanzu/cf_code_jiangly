// url:https://codeforces.com/contest/1680/problem/C
// time:2022-05-16 16:50:35
// name:C-BinaryString

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int n = s.length();
    
    std::vector<int> s0(n + 1), s1(n + 1);
    for (int i = 0; i < n; i++) {
        s0[i + 1] = s0[i] + (s[i] == '0');
        s1[i + 1] = s1[i] + (s[i] == '1');
    }
    
    int ans = n;
    int t = s1[n];
    for (int i = 0; i + t <= n; i++) {
        ans = std::min(ans, std::max(s0[i + t] - s0[i], s1[i] + t - s1[i + t]));
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
