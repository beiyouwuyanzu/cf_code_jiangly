// url:https://codeforces.com/contest/1616/problem/A
// time:2021-12-29 18:37:51
// name:A-IntegerDiversity

#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    
    int cnt[101] = {};
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        cnt[std::abs(x)]++;
    }
    int ans = (cnt[0] > 0);
    for (int i = 1; i <= 100; i++) {
        ans += std::min(2, cnt[i]);
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

