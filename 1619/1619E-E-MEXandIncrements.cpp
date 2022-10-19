// url:https://codeforces.com/contest/1619/problem/E
// time:2021-12-20 18:10:54
// name:E-MEXandIncrements

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> cnt(n + 1);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        cnt[x]++;
    }
    
    i64 ans = 0;
    std::vector<int> s;
    for (int v = 0; v <= n; v++) {
        if (ans == -1) {
            std::cout << "-1" << " \n"[v == n];
            continue;
        }
        std::cout << ans + cnt[v] << " \n"[v == n];
        
        while (cnt[v]--) {
            s.push_back(v);
        }
        
        if (s.empty()) {
            ans = -1;
        } else {
            ans += v - s.back();
            s.pop_back();
        }
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

