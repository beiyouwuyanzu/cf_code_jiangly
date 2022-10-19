// url:https://codeforces.com/contest/1677/problem/A
// time:2022-05-08 17:39:03
// name:A-TokitsukazeandStrangeInequality

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
    }
    
    std::vector<int> cnt(n);
    i64 ans = 0;
    for (int b = 0; b < n; b++) {
        int d = 0;
        for (int c = n - 1; c > b; c--) {
            ans += cnt[c] * d;
            d += p[c] < p[b];
            cnt[c] += p[b] < p[c];
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
