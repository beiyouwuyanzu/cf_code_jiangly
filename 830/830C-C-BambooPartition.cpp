//url:https://codeforces.com/contest/830/problem/C
//time:2021-03-31 08:37:38
//name:C-BambooPartition

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    i64 k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        k += a[i];
    }
    i64 ans = 1;
    i64 x = 0;
    for (int i = 0; i < n; i++) {
        x += a[i];
    }
    std::vector<std::pair<int, int>> c;
    for (int i = 0; i < n; i++) {
        int last = 0;
        for (int j = 1; j <= a[i]; ) {
            int v = (a[i] + j - 1) / j;
            if (last != 0) {
                c.emplace_back(j, v - last);
            }
            if (v == 1) {
                break;
            }
            last = v;
            j = (a[i] - 1) / (v - 1) + 1;
        }
    }
    int last = 1;
    std::sort(c.begin(), c.end());
    for (auto [v, d] : c) {
        if (last <= k / x) {
            ans = std::max(ans, k / x);
        }
        x += d;
        last = v;
    }
    if (last <= k / x) {
        ans = std::max(ans, k / x);
    }
    std::cout << ans << "\n";
    return 0;
}

