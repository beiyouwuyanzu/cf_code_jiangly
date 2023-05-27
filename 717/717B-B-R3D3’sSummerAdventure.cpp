// url:https://codeforces.com/contest/717/problem/B
// time:2023-03-15 16:18:50
// name:B-R3D3’sSummerAdventure

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, c0, c1;
    std::cin >> N >> c0 >> c1;
    
    if (c1 < c0) {
        std::swap(c0, c1);
    }
    
    if (c0 == 0) {
        i64 ans = 1LL * (N - 1) * c1;
        std::cout << ans << "\n";
        return 0;
    }
    
    i64 lo = 0, hi = 1E10;
    
    auto get = [&](i64 x, bool prec = false) {
        i64 cnt = 1;
        i64 sum = 0;
        for (i64 i = 0; i * c1 <= x; i++) {
            i64 j = (x - i * c1) / c0;
            i64 v = 1;
            i64 n = i + j + 1, m = j;
            if (m > n - m) {
                m = n - m;
            }
            for (i64 j = 1; j <= m; j++) {
                v = v * (n - j + 1) / j;
                if (v > N && !prec) {
                    break;
                }
            }
            cnt += v;
            sum += v * c1 * i;
            if (j > 0) {
                v = 1;
                n = i + j + 1, m = j - 1;
                if (m > n - m) {
                    m = n - m;
                }
                for (i64 j = 1; j <= m; j++) {
                    v = v * (n - j + 1) / j;
                    if (v > N && !prec) {
                        break;
                    }
                }
                sum += v * c0 * (i + 1);
            }
            if (cnt > N && !prec) {
                break;
            }
        }
        sum += 1LL * (N - 1) * (c0 + c1);
        return std::pair(cnt, sum);
    };
    while (lo < hi) {
        i64 x = (lo + hi) / 2;
        
        if (get(x).first >= N) {
            hi = x;
        } else {
            lo = x + 1;
        }
    }
    
    auto [cnt, sum] = get(lo, true);
    // std::cerr << lo << " " << cnt << " " << sum << "\n";
    sum -= (cnt - N) * lo;
    std::cout << sum << "\n";
    
    return 0;
}

