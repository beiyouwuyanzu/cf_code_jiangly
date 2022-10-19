// url:https://codeforces.com/contest/1515/problem/C
// time:2021-05-02 17:43:54
// name:C-PhoenixandTowers

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
        int n, m, x;
        std::cin >> n >> m >> x;
        std::vector<int> h(n);
        std::vector<int> a(m);
        for (int i = 0; i < n; i++) {
            std::cin >> h[i];
        }
        std::set<std::pair<int, int>> s;
        for (int i = 0; i < m; i++) {
            s.emplace(0, i);
        }
        std::vector<int> y(n);
        for (int i = 0; i < n; i++) {
            auto [v, j] = *s.begin();
            s.erase(s.begin());
            y[i] = j;
            a[j] += h[i];
            s.emplace(a[j], j);
        }
        std::cout << "YES\n";
        for (int i = 0; i < n; i++) {
            std::cout << y[i] + 1 << " \n"[i == n - 1];
        }
    }
    return 0;
}
