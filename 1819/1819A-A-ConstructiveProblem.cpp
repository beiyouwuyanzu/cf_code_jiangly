// url:https://codeforces.com/contest/1819/problem/A
// time:2023-04-19 09:44:25
// name:A-ConstructiveProblem

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    std::vector<int> f(n + 2);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (a[i] <= n + 1) {
            f[a[i]] = 1;
        }
    }
    int m = 0;
    while (f[m]) {
        m++;
    }
    
    if (!f[m + 1]) {
        if (m < n) {
            std::cout << "Yes\n";
        } else {
            std::cout << "No\n";
        }
        return;
    }
    
    int l = 0, r = n - 1;
    while (a[l] != m + 1) {
        l++;
    }
    while (a[r] != m + 1) {
        r--;
    }
    
    f.assign(n + 2, 0);
    for (int i = l; i <= r; i++) {
        a[i] = m;
    }
    
    for (auto x : a) {
        if (x <= n + 1) {
            f[x] = 1;
        }
    }
    int newm = 0;
    while (f[newm]) {
        newm++;
    }
    if (newm == m + 1) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
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
