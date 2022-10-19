// url:https://codeforces.com/contest/1674/problem/D
// time:2022-05-02 17:48:01
// name:D-A-B-CSort

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    for (int i = n - 2; i >= 0; i -= 2) {
        if (a[i] > a[i + 1]) {
            std::swap(a[i], a[i + 1]);
        }
    }
    
    if (std::is_sorted(a.begin(), a.end())) {
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
