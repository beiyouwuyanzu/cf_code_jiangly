// url:https://codeforces.com/contest/1744/problem/E2
// time:2022-10-18 14:19:30
// name:E2-DivisibleNumbers(hardversion)

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    
    std::map<int, int> r;
    int x = a;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            r[i]++;
            x /= i;
            i--;
        }
    }
    if (x > 1) {
        r[x]++;
    }
    x = b;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            r[i]++;
            x /= i;
            i--;
        }
    }
    if (x > 1) {
        r[x]++;
    }
    
    std::array<i64, 2> ans{-1, -1};
    
    auto dfs = [&](auto self, auto it, auto x) {
        if (it == r.end()) {
            auto y = 1LL * a * b / x;
            auto u = (a / x + 1) * x;
            auto v = (b / y + 1) * y;
            if (u <= c && v <= d) {
                ans = {u, v};
            }
            return;
        }
        auto [p, c] = *it;
        for (int i = 0; i <= c; i++) {
            self(self, std::next(it), x);
            x *= p;
        }
    };
    dfs(dfs, r.begin(), 1LL);
    
    std::cout << ans[0] << " " << ans[1] << "\n";
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
