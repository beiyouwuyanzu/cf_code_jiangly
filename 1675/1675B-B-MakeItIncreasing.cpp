// url:https://codeforces.com/contest/1675/problem/B
// time:2022-05-05 17:37:41
// name:B-MakeItIncreasing

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int ans = 0;
    for (int i = n - 2; i >= 0; i--) {
        if (a[i + 1] == 0) {
            std::cout << "-1\n";
            return;
        }
        while (a[i] >= a[i + 1]) {
            a[i] /= 2;
            ans++;
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
