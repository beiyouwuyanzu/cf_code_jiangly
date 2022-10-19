// url:https://codeforces.com/contest/1680/problem/D
// time:2022-05-16 19:43:21
// name:D-DogWalking

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    auto solve = [&]() {
        std::vector<i64> sum(n + 1);
        std::vector<int> cnt(n + 1);
        for (int i = 0; i < n; i++) {
            sum[i + 1] = sum[i] + a[i];
        }
        for (int i = 0; i < n; i++) {
            cnt[i + 1] = cnt[i] + (a[i] == 0);
        }
        i64 ans = -1;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                i64 sl = sum[i];
                i64 sm = sum[j] - sum[i];
                i64 sr = sum[n] - sum[j];
                
                int cl = cnt[i];
                int cm = cnt[j] - cnt[i];
                int cr = cnt[n] - cnt[j];
                
                sl -= 1LL * cl * k;
                sm += 1LL * cm * k;
                sr -= 1LL * cr * k;
                
                i64 s = sl + sm + sr;
                if (s > 2LL * cm * k) {
                    continue;
                }
                if (s < -2LL * (cl + cr) * k) {
                    continue;
                }
                i64 res = -sl - sr;
                if (s < 0) {
                    res -= -s;
                }
                ans = std::max(ans, res + 1);
            }
        }
        return ans;
    };
    
    i64 ans = solve();
    
    for (auto &x : a) {
        x = -x;
    }
    
    ans = std::max(ans, solve());
    
    std::cout << ans << "\n";
    
    return 0;
}
