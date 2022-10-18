//url:https://codeforces.com/contest/1472/problem/E
//time:2021-01-04 17:48:06
//name:E-CorrectPlacement

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> h(n), w(n);
        for (int i = 0; i < n; i++) {
            std::cin >> h[i] >> w[i];
            if (h[i] > w[i]) {
                std::swap(h[i], w[i]);
            }
        }
        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);
        std::sort(p.begin(), p.end(), [&](int i, int j) {
            return h[i] < h[j];
        });
        int u = -1;
        std::vector<int> ans(n, -1);
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && h[p[i]] == h[p[j]]) {
                j++;
            }
            for (int k = i; k < j; k++) {
                if (u != -1 && w[u] < w[p[k]]) {
                    ans[p[k]] = u;
                }
            }
            for (int k = i; k < j; k++) {
                if (u == -1 || (w[u] > w[p[k]])) {
                    u = p[k];
                }
            }
            i = j;
        }
        for (int i = 0; i < n; i++) {
            std::cout << ans[i] + (ans[i] >= 0) << " \n"[i == n - 1];
        }
    }
    return 0;
}
