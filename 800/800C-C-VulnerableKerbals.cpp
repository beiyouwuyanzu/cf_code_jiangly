//url:https://codeforces.com/contest/800/problem/C
//time:2021-01-03 16:13:38
//name:C-VulnerableKerbals

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int inverse(int a, int m) {
    int g = m, r = a, x = 0, y = 1;
    while (r != 0) {
        int q = g / r;
        g %= r;
        std::swap(g, r);
        x -= q * y;
        std::swap(x, y);
    }
    return x < 0 ? x + m : x;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<bool> good(m);
    for (int i = 0; i < m; i++) {
        good[i] = true;
    }
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        good[x] = false;
    }
    std::vector<int> divisors;
    for (int i = 1; i <= m; i++) {
        if (m % i == 0) {
            divisors.push_back(i);
        }
    }
    std::vector<std::vector<int>> x(m + 1);
    std::vector<int> dp(m + 1), g(m + 1);
    for (int i = 0; i < m; i++) {
        if (good[i]) {
            x[i == 0 ? m : std::gcd(i, m)].push_back(i);
        }
    }
    int ans = 0, f = 0;
    for (auto d : divisors) {
        dp[d] += x[d].size();
        for (auto q : divisors) {
            if (q % d == 0 && dp[q] < dp[d]) {
                dp[q] = dp[d];
                g[q] = d;
            }
        }
        if (dp[d] > ans) {
            ans = dp[d];
            f = d;
        }
    }
    std::cout << ans << "\n";
    std::vector<int> a;
    for (int i = f; i != 0; i = g[i]) {
        a.insert(a.end(), x[i].begin(), x[i].end());
    }
    a.push_back(1);
    std::reverse(a.begin(), a.end());
    for (int i = 1; i <= ans; i++) {
        int g = std::gcd(a[i - 1], m);
        int x = inverse(a[i - 1] / g, m / g);
        x = i64(x) * a[i] / g % m;
        std::cout << x << " \n"[i == ans];
    }
    return 0;
}
