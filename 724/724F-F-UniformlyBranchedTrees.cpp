// url:https://codeforces.com/contest/724/problem/F
// time:2021-12-23 18:24:26
// name:F-UniformlyBranchedTrees

#include <bits/stdc++.h>

using i64 = long long;

int power(int a, int b, int p) {
    int res = 1;
    for (; b > 0; b /= 2, a = 1LL * a * a % p) {
        if (b % 2 == 1) {
            res = 1LL * res * a % p;
        }
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, d, P;
    std::cin >> n >> d >> P;
    
    if (n <= 2) {
        std::cout << "1\n";
        return 0;
    }
    
    n -= 2;
    if (n % (d - 1) != 0) {
        std::cout << "0\n";
        return 0;
    }
    n /= (d - 1);
    
    std::vector<int> f(n + 1);
    f[0] = 1;
    
    std::vector g(d + 1, std::vector<int>(n + 1));
    for (int i = 0; i <= d; i++) {
        g[i][0] = 1;
    }
    
    std::vector<int> fac(d + 1), invfac(d + 1);
    fac[0] = 1;
    for (int i = 1; i <= d; i++) {
        fac[i] = 1LL * fac[i - 1] * i % P;
    }
    for (int i = 0; i <= d; i++) {
        invfac[i] = power(fac[i], P - 2, P);
    }
    
    for (int i = 1; i <= n; i++) {
        f[i] = g[d - 1][i - 1];
        for (int c = d; c >= 0; c--) {
            for (int j = 0; j <= n; j++) {
                for (int k = 1, v = 1; k + c <= d && j + k * i <= n; k++) {
                    v = 1LL * v * (f[i] + k - 1) % P;
                    int &res = g[c + k][j + k * i];
                    res = (res + 1LL * v * invfac[k] % P * g[c][j]) % P;
                }
            }
        }
    }
    
    int ans = g[d][n - 1];
    for (int i = 1; i < n; i++) {
        ans = (ans + 1LL * (P + 1) / 2 * (P - f[i]) % P * f[n - i]) % P;
    }
    if (n % 2 == 0) {
        ans = (ans + 1LL * f[n / 2] * (P + 1) / 2) % P;
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
