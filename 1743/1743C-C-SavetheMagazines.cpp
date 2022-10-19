// url:https://codeforces.com/contest/1743/problem/C
// time:2022-10-17 17:49:40
// name:C-SavetheMagazines

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    for (int i = 0, j = -1; i < n; i++) {
        if (s[i] == '0') {
            j = i;
        } else if (j >= 0 && a[i] < a[j]) {
            std::swap(s[i], s[j]);
            j = i;
        }
    }
    
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            ans += a[i];
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
