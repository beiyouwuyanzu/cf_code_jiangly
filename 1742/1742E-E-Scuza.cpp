// url:https://codeforces.com/contest/1742/problem/E
// time:2022-10-13 18:01:29
// name:E-Scuza

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    std::vector<i64> s(n + 1);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        s[i + 1] = s[i] + a[i];
    }
    for (int i = 1; i < n; i++) {
        a[i] = std::max(a[i], a[i - 1]);
    }
    
    for (int i = 0; i < q; i++) {
        int k;
        std::cin >> k;
        
        std::cout << s[std::upper_bound(a.begin(), a.end(), k) - a.begin()] << " \n"[i == q - 1];
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

