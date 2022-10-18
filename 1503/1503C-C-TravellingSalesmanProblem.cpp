//url:https://codeforces.com/contest/1503/problem/C
//time:2021-04-03 18:14:03
//name:C-TravellingSalesmanProblem

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n), c(n);
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> c[i];
        ans += c[i];
        c[i] += a[i];
    }
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return a[i] < a[j];
    });
    int r = a[p[0]];
    for (int i = 0; i < n; i++) {
        if (a[p[i]] > r) {
            ans += a[p[i]] - r;
        }
        r = std::max(r, c[p[i]]);
    }
    std::cout << ans << "\n";
    return 0;
}

