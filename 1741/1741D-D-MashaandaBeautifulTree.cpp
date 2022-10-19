// url:https://codeforces.com/contest/1741/problem/D
// time:2022-10-11 17:55:45
// name:D-MashaandaBeautifulTree

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    int ans = 0;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    
    bool ok = true;
    auto work = [&](auto self, auto &a, auto l, auto r) {
        if (r - l == 1) {
            if (a[l] != l) {
                ok = false;
            }
            return;
        }
        int m = (l + r) / 2;
        if (!std::count(a.begin() + l, a.begin() + m, l)) {
            std::rotate(a.begin() + l, a.begin() + m, a.begin() + r);
            ans++;
        }
        self(self, a, l, m);
        self(self, a, m, r);
    };
    
    work(work, a, 0, n);
    if (!ok) {
        ans = -1;
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

