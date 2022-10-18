//url:https://codeforces.com/contest/1091/problem/F
//time:2021-07-15 22:39:05
//name:F-NewYearandtheMallardExpedition

#include <bits/stdc++.h>

using i64 = long long;

constexpr i64 inf = 1e18;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<i64> l(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i];
    }
    
    std::string s;
    std::cin >> s;
    
    i64 cnt[6] = {};
    cnt[5] = inf;
    
    i64 ans = 0;
    
    for (int i = 0; i < n; i++) {
        if (s[i] == 'W') {
            cnt[3] = std::max(cnt[3], inf);
            cnt[1] += 2 * l[i];
        } else if (s[i] == 'G') {
            cnt[2] += 2 * l[i];
        }
        
        ans += l[i];
        i64 t = l[i];
        for (int j = 1; t > 0; j++) {
            i64 v = std::min(cnt[j], t);
            cnt[j] -= v;
            t -= v;
            ans += v * j;
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
