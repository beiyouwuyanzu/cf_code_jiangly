//url:https://codeforces.com/contest/1470/problem/B
//time:2021-01-05 17:47:16
//name:B-StrangeDefinition

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int N = 1e6;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<int> minp(N + 1);
    for (int i = 2; i <= N; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            for (int j = 2 * i; j <= N; j += i) {
                if (minp[j] == 0) {
                    minp[j] = i;
                }
            }
        }
    }
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        std::vector<std::vector<int>> p(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
            int x = a[i];
            while (x > 1) {
                int q = minp[x];
                int t = 0;
                while (minp[x] == q) {
                    x /= q;
                    t++;
                }
                if (t % 2 == 1) {
                    p[i].push_back(q);
                }
            }
        }
        std::sort(p.begin(), p.end());
        int ans0 = 0, ans1 = 0;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && p[i] == p[j]) {
                j++;
            }
            ans0 = std::max(ans0, j - i);
            if (p[i].empty() || (j - i) % 2 == 0) {
                ans1 += j - i;
            }
            i = j;
        }
        ans1 = std::max(ans1, ans0);
        int q;
        std::cin >> q;
        while (q--) {
            i64 w;
            std::cin >> w;
            if (w == 0) {
                std::cout << ans0 << "\n";
            } else {
                std::cout << ans1 << "\n";
            }
        }
    }
    return 0;
}
