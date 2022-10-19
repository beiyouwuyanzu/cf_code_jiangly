// url:https://codeforces.com/contest/1686/problem/A
// time:2022-05-30 06:03:41
// name:A-EverythingEverywhereAllButOne

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int sum = std::accumulate(a.begin(), a.end(), 0);
    for (int i = 0; i < n; i++) {
        if (sum == n * a[i]) {
            std::cout << "YES\n";
            return;
        }
    }
    
    std::cout << "NO\n";
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
