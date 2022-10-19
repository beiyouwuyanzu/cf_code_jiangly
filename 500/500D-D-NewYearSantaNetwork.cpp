// url:https://codeforces.com/contest/500/problem/D
// time:2021-06-22 11:53:26
// name:D-NewYearSantaNetwork

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<std::tuple<int, int>>> e(n);
    std::vector<int> len(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b >> len[i];
        a--;
        b--;
        e[a].emplace_back(b, i);
        e[b].emplace_back(a, i);
    }
    std::vector<int> siz(n);
    std::vector<i64> w(n - 1);
    i64 sum = 0;
    std::function<void(int, int)> dfs = [&](int u, int p) {
        siz[u] = 1;
        for (auto [v, j] : e[u]) {
            if (v == p) {
                continue;
            }
            dfs(v, u);
            siz[u] += siz[v];
            w[j] = i64(siz[v]) * (n - siz[v]);
            sum += w[j] * len[j];
        }
    };
    dfs(0, -1);
    int q;
    std::cin >> q;
    std::cout << std::fixed << std::setprecision(10);
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        x--;
        sum += (y - len[x]) * w[x];
        len[x] = y;
        double ans = double(sum) * 6 / n / (n - 1);
        std::cout << ans << "\n";
    }
    return 0;
}
