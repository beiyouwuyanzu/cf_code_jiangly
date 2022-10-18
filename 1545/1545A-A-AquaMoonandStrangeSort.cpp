//url:https://codeforces.com/contest/1545/problem/A
//time:2021-07-11 17:07:31
//name:A-AquaMoonandStrangeSort

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) { return a[i] < a[j]; });
    
    bool ok = true;
    for (int l = 0, r; l < n; l = r) {
        for (r = l; r < n && a[p[l]] == a[p[r]]; r++)
            ;
        
        int cnt = 0;
        for (int i = l; i < r; i++) {
            cnt += i % 2;
            cnt -= p[i] % 2;
        }
        
        if (cnt != 0) {
            ok = false;
        }
    }
    
    if (ok) {
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
