// url:https://codeforces.com/contest/494/problem/C
// time:2021-06-21 18:04:41
// name:C-HelpingPeople

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int mx = *std::max_element(a.begin(), a.end());
    std::vector<std::tuple<int, int, double>> seg(q + 1);
    for (int i = 0; i < q; i++) {
        int l, r;
        double p;
        std::cin >> l >> r >> p;
        l--;
        seg[i] = {l, -r, p};
    }
    seg[q] = {0, -n, 0};
    q++;
    std::sort(seg.begin(), seg.end());
    for (int i = 0; i < n; i++) {
        a[i] = std::max(-q, a[i] - mx);
    }
    std::vector dp(q, std::vector<double>(2 * q + 1, 1));
    for (int i = q - 1; i >= 0; i--) {
        auto [l, r, p] = seg[i];
        r = -r;
        int mx = -q;
        int lst = l;
        for (int j = i + 1; j < q && std::get<0>(seg[j]) < r; j++) {
            auto [L, R, P] = seg[j];
            R = -R;
            if (L < lst) {
                continue;
            }
            while (lst < L) {
                mx = std::max(mx, a[lst++]);
            }
            for (int k = 0; k <= 2 * q; k++) {
                dp[i][k] *= dp[j][k];
            }
            lst = R;
        }
        while (lst < r) {
            mx = std::max(mx, a[lst++]);
        }
        for (int j = -q; j < mx; j++) {
            dp[i][j + q] = 0;
        }
        for (int j = 2 * q; j; j--) {
            dp[i][j] *= (1 - p);
            dp[i][j] += dp[i][j - 1] * p;
        }
    }
    double ans = mx + q;
    for (int j = 0; j < q; j++) {
        ans -= dp[0][q + j];
    }
    std::cout << std::fixed << std::setprecision(10) << ans << "\n";
    return 0;
}
