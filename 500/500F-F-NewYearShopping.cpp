// url:https://codeforces.com/contest/500/problem/F
// time:2021-06-22 18:17:34
// name:F-NewYearShopping

#include <bits/stdc++.h>
using i64 = long long;
constexpr int C = 4000;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, p;
    std::cin >> n >> p;
    std::vector<std::tuple<int, int, int>> item(n);
    for (int i = 0; i < n; i++) {
        int c, h, t;
        std::cin >> c >> h >> t;
        item[i] = {t, c, h};
    }
    std::sort(item.begin(), item.end());
    int q;
    std::cin >> q;
    std::vector<std::tuple<int, int, int>> cust(q);
    for (int i = 0; i < q; i++) {
        int a, b;
        std::cin >> a >> b;
        cust[i] = {a, b, i};
    }
    std::sort(cust.begin(), cust.end());
    std::vector<int> ans(q);
    std::vector left(1, std::vector<int>(C + 1)), right(1, std::vector<int>(C + 1));
    auto change = [&](std::vector<int> f, int c, int h) {
        for (int i = C; i >= c; i--) {
            f[i] = std::max(f[i], f[i - c] + h);
        }
        return f;
    };
    for (int i = 0, L = 0, R = 0; i < q; i++) {
        auto [a, b, i1] = cust[i];
        while (R < n && std::get<0>(item[R]) <= a) {
            auto [t, c, h] = item[R++];
            right.push_back(change(right.back(), c, h));
        }
        while (L < n && std::get<0>(item[L]) + p <= a) {
            if (left.size() == 1) {
                right.resize(1);
                for (int j = R - 1; j >= L; j--) {
                    auto [t, c, h] = item[j];
                    left.push_back(change(left.back(), c, h));
                }
            }
            left.pop_back();
            L++;
        }
        for (int j = 0; j <= b; j++) {
            ans[i1] = std::max(ans[i1], left.back()[j] + right.back()[b - j]);
        }
    }
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    return 0;
}
