//url:https://codeforces.com/contest/1730/problem/F
//time:2022-09-25 18:59:36
//name:F-AlmostSorted

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> p(n), pos(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
        pos[p[i]] = i;
    }
    
    std::vector<int> f(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + k < i; j++) {
            f[i] += pos[j] > pos[i];
        }
    }
    
    std::vector dp(n, std::vector<int>(1 << k, inf));
    for (int i = 0; i < n; i++) {
        if (i <= k) {
            dp[i][(1 << i) - 1] = 0;
        }
        for (int mask = (1 << k) - 1; mask >= 0; mask--) {
            int ex = mask > 0 ? i - 1 - std::__lg(mask) : i + 1;
            if (dp[i][mask] == inf) {
                continue;
            }
            for (int j = ex; j <= ex + k && j < n; j++) {
                if (j == i || (j < i && (~mask >> (i - j - 1) & 1))) {
                    continue;
                }
                int val = dp[i][mask] + f[j];
                int ni = std::max(i, j);
                int nmask = mask << (ni - i);
                if (j > i) {
                    nmask |= (1 << (j - i - 1)) - 1;
                } else {
                    nmask ^= (1 << (i - j - 1));
                }
                assert(nmask < (1 << k));
                for (int x = std::max(0, j - k); x <= i; x++) {
                    if (x == j) {
                        continue;
                    }
                    if (x == i || (~mask >> (i - 1 - x) & 1)) {
                        val += pos[x] > pos[j];
                    }
                }
                // std::cerr << i << " " << mask << " " << j << " " << ni << " " << nmask << " " << val << "\n";
                dp[ni][nmask] = std::min(dp[ni][nmask], val);
            }
        }
    }
    
    std::cout << dp[n - 1][0] << "\n";
    
    return 0;
}
