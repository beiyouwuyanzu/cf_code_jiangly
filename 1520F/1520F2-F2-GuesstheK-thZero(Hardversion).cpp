// url:https://codeforces.com/contest/1520/problem/F2
// time:2021-05-05 18:21:55
// name:F2-GuesstheK-thZero(Hardversion)

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int query(int l, int r) {
    int ans;
    std::cout << "? " << l + 1 << " " << r << std::endl;
    std::cin >> ans;
    return r - l - ans;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, t;
    std::cin >> n >> t;
    int b = (n + 15) >> 4;
    std::vector<int> sum(b + 1);
    for (int i = 0; i < t; i++) {
        int k;
        std::cin >> k;
        k--;
        if (i == 0) {
            for (int j = 1; j <= b; j++) {
                sum[j] = query(0, std::min(n, j << 4));
            }
        }
        int l = (std::upper_bound(sum.begin(), sum.end(), k) - 1 - sum.begin()) << 4;
        int r = std::min(n, l + 16);
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (query(0, m) <= k) {
                l = m;
            } else {
                r = m;
            }
        }
        std::cout << "! " << r << std::endl;
        for (int i = (l >> 4) + 1; i <= b; i++) {
            sum[i]--;
        }
    }
    return 0;
}
