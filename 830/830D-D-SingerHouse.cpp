//url:https://codeforces.com/contest/830/problem/D
//time:2021-03-31 07:31:21
//name:D-SingerHouse

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
constexpr int P = 1000000007;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> f(n + 1, std::vector<int>(n + 2)), C(n + 1, std::vector<int>(n + 1));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
        }
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i][0] = 1;
        for (int j = 1; j <= n - i + 1; j++) {
            for (int k = 0; k <= j; k++) {
                f[i][j] = (f[i][j] + i64(f[i - 1][k]) * f[i - 1][j - k]) % P;
            }
            for (int k = 0; k < j; k++) {
                f[i][j] = (f[i][j] + 2ll * f[i - 1][k + 1] * (k + 1) % P * f[i - 1][j - k] % P * (j - k)) % P;
                f[i][j] = (f[i][j] + 2ll * (i64(f[i - 1][k + 2]) * (k + 2) % P * (k + 1) + i64(f[i - 1][k + 1]) * 2 * (k + 1)) % P * f[i - 1][j - k - 1]) % P;
                f[i][j] = (f[i][j] + i64(f[i - 1][k]) * f[i - 1][j - k - 1]) % P;
            }
        }
    }
    std::cout << f[n][1] << "\n";
    return 0;
}

