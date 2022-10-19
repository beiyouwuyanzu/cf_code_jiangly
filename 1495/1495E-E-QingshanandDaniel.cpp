// url:https://codeforces.com/contest/1495/problem/E
// time:2021-03-10 17:51:34
// name:E-QingshanandDaniel

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 1000000007;
int seed = 0, base = 0;
int rnd() {
    int ret = seed;
    seed = (i64(seed) * base + 233) % P;
    return ret;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> p(m + 1), k(m), b(m), w(m);
    for (int i = 0; i < m; i++) {
        std::cin >> p[i + 1] >> k[i] >> b[i] >> w[i];
    }
    std::vector<int> t(n);
    std::vector<int> a(n);
    for (int i = 0; i < m; i++) {
        seed = b[i];
        base = w[i];
        for (int j = p[i]; j < p[i + 1]; j++) {
            t[j] = rnd() % 2;
            a[j] = rnd() % k[i] + 1;
        }
    }
    auto A = a;
    i64 sum[2] {};
    for (int i = 0; i < n; i++) {
        sum[t[i]] += a[i];
    }
    if (sum[0] > sum[1]) {
        std::swap(sum[0], sum[1]);
        for (int i = 0; i < n; i++) {
            t[i] = !t[i];
        }
    }
    i64 x = t[0];
    for (int i = 0; i < n; i++) {
        if (t[i] == 0) {
            x += a[i];
            a[i] = 0;
        } else {
            int v = std::min<i64>(x, a[i]);
            a[i] -= v;
            x -= v;
        }
    }
    for (int i = 0; i < n; i++) {
        if (t[i] == 1) {
            int v = std::min<i64>(x, a[i]);
            a[i] -= v;
            x -= v;
        }
    }
    int ans = 1;
    for (int i = 0; i < n; i++) {
        ans = (1 + ((A[i] - a[i]) ^ (i64(i + 1) * (i + 1)))) % P * ans % P;
    }
    std::cout << ans << "\n";
    return 0;
}

