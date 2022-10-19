// url:https://codeforces.com/contest/1676/problem/F
// time:2022-05-10 17:57:21
// name:F-LongestStrike

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    int l = -1, r = -1;
    std::map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        cnt[x]++;
    }
    
    int last = -1;
    int begin = -1;
    for (auto [x, c] : cnt) {
        if (c < k) {
            continue;
        }
        if (last != x - 1) {
            begin = x;
        }
        last = x;
        if (l == -1 || x - begin > r - l) {
            l = begin;
            r = x;
        }
    }
    
    if (l == -1) {
        std::cout << "-1\n";
    } else {
        std::cout << l << " " << r << "\n";
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
