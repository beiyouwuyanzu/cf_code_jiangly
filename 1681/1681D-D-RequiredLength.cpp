//url:https://codeforces.com/contest/1681/problem/D
//time:2022-05-23 18:00:21
//name:D-RequiredLength

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    i64 lim = 1;
    for (int i = 1; i < n; i++) {
        lim *= 10;
    }
    
    i64 x;
    std::cin >> x;
    
    std::map<i64, int> f;
    std::function<int(i64)> rec = [&](i64 x) -> int {
        if (x >= lim) {
            return 0;
        }
        if (f.contains(x)) {
            return f[x];
        }
        int &res = f[x] = inf;
        auto s = std::to_string(x);
        for (auto c : s) {
            int d = c - '0';
            if (d >= 2) {
                res = std::min(res, 1 + rec(x * d));
            }
        }
        return res;
    };
    
    auto ans = rec(x);
    if (ans == inf) {
        ans = -1;
    }
    std::cout << ans << "\n";
    
    return 0;
}
