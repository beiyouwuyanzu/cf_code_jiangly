// url:https://codeforces.com/contest/1682/problem/A
// time:2022-05-22 17:45:51
// name:A-PalindromicIndices

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    int l = n / 2;
    while (l > 0 && s[l - 1] == s[l]) {
        l--;
    }
    int r = n - l - 1;
    std::cout << r - l + 1 << "\n";
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
