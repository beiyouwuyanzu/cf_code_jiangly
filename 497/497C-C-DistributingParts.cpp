// url:https://codeforces.com/contest/497/problem/C
// time:2021-06-20 20:25:42
// name:C-DistributingParts

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n;
    std::vector<std::tuple<int, int, int>> part(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        part[i] = {a, b, i};
    }
    std::cin >> m;
    std::vector<std::tuple<int, int, int, int>> actor(m);
    for (int i = 0; i < m; i++) {
        int c, d, k;
        std::cin >> c >> d >> k;
        actor[i] = {c, d, k, i};
    }
    std::sort(part.begin(), part.end());
    std::sort(actor.begin(), actor.end());
    std::set<std::tuple<int, int, int>> s;
    std::vector<int> ans(n);
    for (int i = 0, j = 0; i < n; i++) {
        auto [a, b, i1] = part[i];
        while (j < m && std::get<0>(actor[j]) <= a) {
            auto [c, d, k, j1] = actor[j];
            s.emplace(d, k, j1);
            j++;
        }
        auto it = s.lower_bound({b, -1, -1});
        if (it == s.end()) {
            std::cout << "NO\n";
            return 0;
        }
        auto [d, k, j1] = *it;
        ans[i1] = j1 + 1;
        s.erase(it);
        if (k > 1) {
            s.emplace(d, k - 1, j1);
        }
    }
    std::cout << "YES\n";
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}
