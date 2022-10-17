//url:https://codeforces.com/contest/1726/problem/C
//time:2022-09-06 17:43:47
//name:C-Jatayu'sBalancedBracketSequence

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    int ans = n + 1;
    for (int i = 0; i < 2 * n - 1; i++) {
        if (s[i] == '(' && s[i + 1] == ')') {
            ans--;
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
