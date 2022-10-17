//url:https://codeforces.com/contest/1725/problem/D
//time:2022-09-04 19:25:45
//name:D-DeducingSortability

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> sum{0};
    while (sum.back() < n) {
        int s = sum.size();
        sum.push_back(sum.back() + (s + 1) / 2);
    }
    
    sum.back() = n;
    
    const int m = sum.size() - 1;
    i64 ans = 0;
    for (int i = 1; i <= m; i++) {
        ans += (sum[i] - sum[i - 1]) * i;
    }
    
    std::cout << ans << "\n";
    
    std::vector<int> maxc(m + 1);
    for (int i = 0; i <= m; i++) {
        maxc[i] = m - 1 - i;
        if (maxc[i] % 2 == 0) {
            maxc[i]--;
        }
    }
    
    int need = n - sum[sum.size() - 2];
    
    std::vector<int> sumk(m + 1);
    
    for (int c = 1; c <= m; c += 2) {
        if (need > 0) {
            need--;
            maxc[m - c] = c;
        }
    }
    
    for (int k = 0; k < m; k++) {
        sumk[k + 1] = sumk[k] + (maxc[k] + 1) / 2;
    }
    assert(sumk[m] == n);
    
    auto get = [&](int x) {
        int kmin = std::lower_bound(sumk.begin(), sumk.end(), x) - sumk.begin();
        kmin = std::max(0, kmin - 20);
        
        i64 L = 1, R = 1LL << 40;
        while (L < R) {
            i64 v = (L + R) / 2;
            
            int cnt = sumk[kmin];
            for (int i = kmin; i < kmin + 40 && i < m; i++) {
                i64 y = v >> (i - kmin);
                if (y % 2 == 0) {
                    y--;
                }
                y = std::min(y, 1LL * maxc[i]);
                cnt += (y + 1) / 2;
            }
            
            if (cnt >= x) {
                R = v;
            } else {
                L = v + 1;
            }
        }
        
        int ctz = __builtin_ctzll(L);
        int k = kmin + ctz;
        int c = L >> ctz;
        return k + c;
    };
    
    for (int i = 0; i < q; i++) {
        int x;
        std::cin >> x;
        
        std::cout << get(x) << "\n";
    }
    
    return 0;
}
