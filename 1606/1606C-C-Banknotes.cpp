//url:https://codeforces.com/contest/1606/problem/C
//time:2022-06-10 11:37:35
//name:C-Banknotes

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        a[i] = 1;
        while (x--) {
            a[i] *= 10;
        }
    }
    
    i64 ans = 0;
    k++;
    for (int i = 0; i < n; i++) {
        int x = std::min(k, i == n - 1 ? k : a[i + 1] / a[i] - 1);
        k -= x;
        ans += 1LL * x * a[i];
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
