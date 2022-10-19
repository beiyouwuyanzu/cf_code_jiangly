// url:https://codeforces.com/contest/1736/problem/C1
// time:2022-10-10 18:47:42
// name:C1-GoodSubarrays(EasyVersion)

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (auto &i : a) {
        std::cin >> i;
        i--;
    }
    
    for (int i = 0; i < n; i++) {
        a[i] -= i;
    }
    
    i64 ans = 0;
    for (int i = 0, j = 0; i < n; i++) {
        while (j < n && a[j] + i >= 0) {
            j++;
        }
        ans += j;
    }
    ans -= 1LL * n * (n - 1) / 2;
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

