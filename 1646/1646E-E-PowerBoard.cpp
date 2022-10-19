// url:https://codeforces.com/contest/1646/problem/E
// time:2022-03-04 20:10:26
// name:E-PowerBoard

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    i64 ans = 1;
    std::vector<bool> good(n + 1, true);
    for (int i = 2; i <= n; i++) {
        if (!good[i]) {
            continue;
        }
        i64 x = i;
        int lg = 1;
        while (x * i <= n) {
            lg++;
            x *= i;
            good[x] = false;
        }
        
        for (int s = 1; s < (1 << lg); s++) {
            i64 lcm = 1;
            int mn = -1;
            for (int i = 0; i < lg; i++) {
                if (s >> i & 1) {
                    if (mn == -1) {
                        mn = i + 1;
                    }
                    lcm = std::min(i64(lg + 1) * m, std::lcm(lcm, i64(i + 1)));
                }
            }
            ans += (__builtin_parity(s) ? 1 : -1) * (m * mn / lcm);
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
