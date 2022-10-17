//url:https://codeforces.com/contest/1726/problem/F
//time:2022-09-06 18:31:25
//name:F-LateForWork(submissionsarenotallowed)

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, t;
    std::cin >> n >> t;
    
    std::vector<int> g(n), c(n);
    for (int i = 0; i < n; i++) {
        std::cin >> g[i] >> c[i];
    }
    
    std::vector<i64> a(n);
    for (int i = 0; i < n - 1; i++) {
        int d;
        std::cin >> d;
        a[i + 1] = a[i] + d;
    }
    
    std::vector<int> s(n), e(n);
    for (int i = 0; i < n; i++) {
        s[i] = (-a[i] - c[i]) % t;
        s[i] = (s[i] + t) % t;
        e[i] = (-a[i] + g[i] - c[i]) % t;
        e[i] = (e[i] + t) % t;
    }
    
    std::map<int, int> f;
    f[0] = n;
    f[t] = n;
    
    auto split = [&](int x) {
        auto it = std::prev(f.upper_bound(x));
        f[x] = it->second;
    };
    
    auto cover = [&](int l, int r, int v) {
        if (l == r) {
            return;
        }
        
        split(l);
        split(r);
        
        for (auto it = f.find(l); it->first < r; it = f.erase(it))
            ;
        
        f[l] = v;
    };
    
    auto get = [&](int x) {
        return std::prev(f.upper_bound(x)) -> second;
    };
    
    std::vector<i64> dp(n);
    for (int i = n - 1; i >= 0; i--) {
        auto j = get(s[i]);
        if (j < n) {
            dp[i] = dp[j] + (s[j] - s[i] + t) % t;
        } else {
            dp[i] = 0;
        }
        
        if (s[i] < e[i]) {
            cover(e[i], t, i);
            cover(0, s[i], i);
        } else {
            cover(e[i], s[i], i);
        }
    }
    
    i64 ans = 1E18;
    for (auto [x, i] : f) {
        if (x == t) {
            continue;
        }
        if (i == n) {
            ans = 0;
        } else {
            int c = f.upper_bound(x)->first - 1;
            ans = std::min(ans, dp[i] + (s[i] - c + t) % t);
        }
    }
    
    ans += a[n - 1];
    std::cout << ans << "\n";
    
    return 0;
}
