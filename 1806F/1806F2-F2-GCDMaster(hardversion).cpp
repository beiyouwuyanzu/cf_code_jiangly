// url:https://codeforces.com/contest/1806/problem/F2
// time:2023-03-20 23:01:25
// name:F2-GCDMaster(hardversion)

#include <bits/stdc++.h>

using i64 = long long;
using i128 = __int128;

std::ostream &operator<<(std::ostream &os, i128 n) {
    std::string s;
    while (n) {
        s += '0' + n % 10;
        n /= 10;
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}

void solve() {
    int n, k;
    i64 m;
    std::cin >> n >> m >> k;
    
    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a.begin(), a.end());
    
    std::vector<int> suf(n + 1);
    std::vector<i128> ssuf(n + 1);
    std::vector<i128> sum(n + 1);
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = suf[i + 1] + (i == n - 1 || a[i] != a[i + 1]);
        ssuf[i] = ssuf[i + 1] + (i == n - 1 || a[i] != a[i + 1]) * a[i];
        sum[i] = sum[i + 1] + a[i];
    }
    
    i128 ans = 0;
    i64 g = 0;
    auto gg = a;
    for (int i = 0; i < n; i++) {
        if (i > 0 && a[i] % g != 0) {
            i64 last = 1;
            for (int j = i; j < n; j++) {
                i64 ng = std::gcd(g, gg[j]);
                gg[j] = ng;
                if (a[j] - a[i] > ng || last >= ng) {
                    continue;
                }
                last = ng;
                int L = std::lower_bound(a.begin(), a.end(), a[j]) - a.begin();
                int R = std::upper_bound(a.begin(), a.end(), a[j]) - a.begin();
                int v = suf[i] - (suf[L] - suf[R]);
                i128 res = ng + ssuf[i] - (ssuf[L] - ssuf[R]);
                if (v <= n - k - 1) {
                    int t = n - k - 1 - v;
                    int lo = i + 1, hi = n;
                    while (lo < hi) {
                        int x = (lo + hi) / 2;
                        int c = n - x - suf[x];
                        if (x <= L) {
                            c -= R - L - (suf[L] - suf[R]);
                        } else if (x < R) {
                            c -= R - x - (suf[x] - suf[R]);
                        }
                        if (c <= t) {
                            hi = x;
                        } else {
                            lo = x + 1;
                        }
                    }
                    res += sum[lo] - ssuf[lo];
                    if (lo <= L) {
                        res -= sum[L] - sum[R] - (ssuf[L] - ssuf[R]);
                    } else if (lo < R) {
                        res -= sum[lo] - sum[R] - (ssuf[lo] - ssuf[R]);
                    }
                    ans = std::max(ans, res);
                }
            }
        }
        g = std::gcd(g, a[i]);
        int v = suf[i + 1];
        if (v <= n - k - 1) {
            i128 res = g + ssuf[i + 1];
            int t = n - k - 1 - v;
            int lo = i + 1, hi = n;
            while (lo < hi) {
                int x = (lo + hi) / 2;
                int c = n - x - suf[x];
                if (c <= t) {
                    hi = x;
                } else {
                    lo = x + 1;
                }
            }
            res += sum[lo] - ssuf[lo];
            ans = std::max(ans, res);
        }
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
