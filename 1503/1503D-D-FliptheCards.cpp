// url:https://codeforces.com/contest/1503/problem/D
// time:2021-04-03 18:30:00
// name:D-FliptheCards

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n), b(n);
    std::vector<int> p(n), q(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> b[i];
        if (std::max(a[i], b[i]) <= n) {
            std::cout << "-1\n";
            return 0;
        }
        int c = std::max(a[i], b[i]) - n - 1;
        p[c] = n - std::min(a[i], b[i]);
        q[c] = a[i] > b[i];
    }
    int m = -1, l = -1;
    int x = 0, y = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] > m) {
            m = p[i];
            if (q[i] == 1) {
                x++;
            } else {
                y++;
            }
        } else {
            if (p[i] < l) {
                std::cout << "-1\n";
                return 0;
            }
            l = p[i];
            if (q[i] == 1) {
                y++;
            } else {
                x++;
            }
        }
        if (i == m) {
            ans += std::min(x, y);
            x = y = 0;
        }
    }
    std::cout << ans << "\n";
    return 0;
}

