// url:https://codeforces.com/contest/1670/problem/A
// time:2022-05-06 18:30:28
// name:A-Prof.Slim

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    int neg = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        if (a[i] < 0) {
            a[i] = -a[i];
            neg++;
        }
    }
    
    int j = std::min_element(a.begin(), a.end()) - a.begin();
    if (!std::is_sorted(a.begin(), a.begin() + j, std::greater()) ||
        !std::is_sorted(a.begin() + j, a.end())) {
        std::cout << "NO\n";
        return;
    }
    int k = 0;
    if (neg >= j && (neg == j || a[neg - 1] == a[j])) {
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
