// url:https://codeforces.com/contest/1807/problem/C
// time:2023-03-20 15:55:19
// name:C-FindandReplace

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    int a[26];
    std::fill(a, a + 26, -1);
    for (int i = 0; i < n; i++) {
        int x = s[i] - 'a';
        if (a[x] == !(i % 2)) {
            std::cout << "NO\n";
            return;
        }
        a[x] = i % 2;
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
