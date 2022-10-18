//url:https://codeforces.com/contest/800/problem/A
//time:2021-01-03 15:55:31
//name:A-VoltageKeepsake

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, p;
    std::cin >> n >> p;
    std::vector<int> a(n), b(n);
    i64 sumA = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> b[i];
        sumA += a[i];
    }
    if (p >= sumA) {
        std::cout << "-1\n";
        return 0;
    }
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 0);
    std::sort(perm.begin(), perm.end(), [&](int i, int j) {
        return i64(b[i]) * a[j] < i64(b[j]) * a[i];
    });
    double ans = 1e10;
    sumA = 0;
    i64 sumB = 0;
    for (int i = 0; i < n; i++) {
        sumA += a[perm[i]];
        sumB += b[perm[i]];
        if (sumA > p) {
            ans = std::min(ans, double(sumB) / (sumA - p));
        }
    }
    std::cout << std::fixed << std::setprecision(10) << ans << "\n";
    return 0;
}
