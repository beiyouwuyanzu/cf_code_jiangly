//url:https://codeforces.com/contest/1623/problem/B
//time:2021-12-28 17:39:41
//name:B-GameonRanges

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> r[i];
        l[i]--;
    }
    for (int i = 0; i < n; i++) {
        int x = l[i];
        for (int j = 0; j < n; j++) {
            if (l[i] == l[j] && r[j] < r[i]) {
                x = std::max(x, r[j]);
            }
        }
        std::cout << l[i] + 1 << " " << r[i] << " " << x + 1 << "\n";
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

