// url:https://codeforces.com/contest/1525/problem/B
// time:2022-03-01 14:35:08
// name:B-PermutationSort

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    if (std::is_sorted(a.begin(), a.end())) {
        std::cout << "0\n";
    } else if (a[0] == 1 || a[n - 1] == n) {
        std::cout << "1\n";
    } else if (a[0] != n || a[n - 1] != 1) {
        std::cout << "2\n";
    } else {
        std::cout << "3\n";
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
