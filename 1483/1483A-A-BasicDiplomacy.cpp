//url:https://codeforces.com/contest/1483/problem/A
//time:2021-03-21 16:28:30
//name:A-BasicDiplomacy

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
        int n, m;
        std::cin >> n >> m;
        std::vector<int> cnt(n);
        std::vector<std::vector<int>> a(m);
        std::vector<int> x(m, -1);
        int lim = (m + 1) / 2;
        for (int i = 0; i < m; i++) {
            int k;
            std::cin >> k;
            a[i].resize(k);
            for (int j = 0; j < k; j++) {
                std::cin >> a[i][j];
                a[i][j]--;
            }
            if (k == 1) {
                cnt[a[i][0]]++;
                x[i] = a[i][0];
            }
        }
        if (*std::max_element(cnt.begin(), cnt.end()) > lim) {
            std::cout << "NO\n";
            continue;
        }
        for (int i = 0; i < m; i++) {
            if (a[i].size() >= 2) {
                for (auto y : a[i]) {
                    if (cnt[y] < lim) {
                        cnt[y]++;
                        x[i] = y;
                        break;
                    }
                }
            }
        }
        std::cout << "YES\n";
        for (int i = 0; i < m; i++) {
            std::cout << x[i] + 1 << " \n"[i == m - 1];
        }
    }
    return 0;
}

