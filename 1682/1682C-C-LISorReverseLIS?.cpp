// url:https://codeforces.com/contest/1682/problem/C
// time:2022-05-22 17:53:12
// name:C-LISorReverseLIS?

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (cnt[x] < 2) {
            cnt[x]++;
        }
    }
    
    int ans = 0, v = 0;
    for (auto [x, c] : cnt) {
        if (c == 2) {
            ans++;
        } else {
            v++;
        }
    }
    ans += (v + 1) / 2;
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
