//url:https://codeforces.com/contest/1718/problem/F
//time:2022-09-28 15:31:54
//name:F-Burenka,anArrayandQueries

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, C, q;
    std::cin >> n >> m >> C >> q;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> minp(m + 1, -1);
    
    std::vector<int> primes;
    for (int i = 2; i <= m; i++) {
        if (minp[i] == -1) {
            primes.push_back(i);
            minp[i] = primes.size() - 1;
        }
        for (auto p : primes) {
            if (i * p > m) {
                break;
            }
            minp[i * p] = minp[p];
            if (i % p == 0) {
                break;
            }
        }
    }
    
    const int nprimes = primes.size();
    const int nsmall = std::lower_bound(primes.begin(), primes.end(), 43) - primes.begin();
    const int nlarge = nprimes - nsmall;
    
    std::vector<std::array<int, 2>> pairs;
    for (int i = nsmall; i < nprimes; i++) {
        for (int j = nsmall; j < i && primes[i] * primes[j] <= C; j++) {
            pairs.push_back({i, j});
        }
    }
    
    const int npairs = pairs.size();
    
    std::vector<int> f(1 << nsmall);
    std::vector fl(1 << nsmall, std::vector<int>(nlarge)), fp(1 << nsmall, std::vector<int>(npairs));
    
    for (int mask = 0; mask < (1 << nsmall); mask++) {
        int c = C;
        for (int i = 0; i < nsmall; i++) {
            if (mask >> i & 1) {
                c /= primes[i];
                c *= -1;
            }
        }
        f[mask] = c;
        for (int i = 0; i < nlarge; i++) {
            fl[mask][i] = -c / primes[nsmall + i];
        }
        for (int i = 0; i < npairs; i++) {
            fp[mask][i] = c / (primes[pairs[i][0]] * primes[pairs[i][1]]);
        }
    }
    
    for (int i = 1; i < (1 << nsmall); i *= 2) {
        for (int j = 0; j < (1 << nsmall); j += 2 * i) {
            for (int k = 0; k < i; k++) {
                f[i + j + k] += f[j + k];
                for (int x = 0; x < nlarge; x++) {
                    fl[i + j + k][x] += fl[j + k][x];
                }
                for (int x = 0; x < npairs; x++) {
                    fp[i + j + k][x] += fp[j + k][x];
                }
            }
        }
    }
    
    std::vector<std::array<int, 3>> queries(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        queries[i] = {l, r, i};
    }
    
    const int B = std::max(1., n / std::sqrt(q));
    
    std::sort(queries.begin(), queries.end(), [&](auto a, auto b) {
        if (a[0] / B != b[0] / B) {
            return a[0] / B < b[0] / B;
        } else {
            return a[1] < b[1];
        }
    });
    
    std::vector pre(nsmall, std::vector<int>(n + 1));
    
    std::vector<std::array<int, 2>> fac(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        for (int x = a[i]; x > 1; ) {
            int j = minp[x];
            while (x % primes[j] == 0) {
                x /= primes[j];
            }
            if (j < nsmall) {
                pre[j][i + 1]++;
            } else if (fac[i][0] == -1) {
                fac[i][0] = j;
            } else {
                fac[i][1] = j;
            }
        }
    }
    
    std::vector<int> cnt(nprimes);
    
    auto add = [&](int i, int t) {
        if (fac[i][0] != -1) {
            cnt[fac[i][0]] += t;
        }
        if (fac[i][1] != -1) {
            cnt[fac[i][1]] += t;
        }
    };
    
    for (int i = 0; i < nsmall; i++) {
        for (int j = 1; j <= n; j++) {
            pre[i][j] += pre[i][j - 1];
        }
    }
    
    std::vector<int> ans(q);
    
    for (int l = 0, r = 0; auto [L, R, i] : queries) {
        while (l > L) {
            add(--l, 1);
        }
        while (r < R) {
            add(r++, 1);
        }
        while (l < L) {
            add(l++, -1);
        }
        while (r > R) {
            add(--r, -1);
        }
        
        int mask = 0;
        for (int i = 0; i < nsmall; i++) {
            if (pre[i][R] != pre[i][L]) {
                mask |= 1 << i;
            }
        }
        
        int res = f[mask];
        for (int i = 0; i < nlarge; i++) {
            if (cnt[nsmall + i]) {
                res += fl[mask][i];
            }
        }
        for (int i = 0; i < npairs; i++) {
            if (cnt[pairs[i][0]] && cnt[pairs[i][1]]) {
                res += fp[mask][i];
            }
        }
        ans[i] = res;
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
