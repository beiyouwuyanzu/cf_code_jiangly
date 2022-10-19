// url:https://codeforces.com/contest/377/problem/B
// time:2021-06-19 22:41:51
// name:B-PreparingfortheContest

#include <bits/stdc++.h>
struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, s;
    std::cin >> n >> m >> s;
    std::vector<std::pair<int, int>> bug(m);
    std::vector<std::tuple<int, int, int>> stu(n);
    for (int i = 0; i < m; i++) {
        std::cin >> bug[i].first;
        bug[i].second = i;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> std::get<1>(stu[i]);
    }
    for (int i = 0; i < n; i++) {
        std::cin >> std::get<0>(stu[i]);
        std::get<2>(stu[i]) = i;
    }
    std::sort(bug.begin(), bug.end());
    std::sort(stu.begin(), stu.end());
    std::vector<int> lim(n);
    for (int i = 0; i < n; i++) {
        int x = std::get<1>(stu[i]);
        lim[i] = std::partition_point(bug.begin(), bug.end(), [&](auto bug) {
            return bug.first <= x;
        }) - bug.begin();
    }
    std::vector<int> ans(m);
    auto check = [&](int x) {
        std::vector<int> res(m);
        DSU t(m + 1);
        for (int i = m; i > 0; i -= x) {
            for (int j = std::max(1, i - x + 1); j < i; j++) {
                t.merge(j - 1, j);
            }
        }
        int cost = 0;
        for (int i = 0; i < n; i++) {
            if (t.leader(lim[i])) {
                int j = t.leader(lim[i]);
                for (int k = std::max(1, j - x + 1); k <= j; k++) {
                    res[bug[k - 1].second] = std::get<2>(stu[i]);
                }
                t.merge(j - 1, j);
                cost += std::get<0>(stu[i]);
                if (cost > s) {
                    return false;
                }
            }
        }
        if (t.leader(m)) {
            return false;
        }
        ans = res;
        return true;
    };
    int lo = 1, hi = m + 1;
    while (lo < hi) {
        int x = (lo + hi) / 2;
        if (check(x)) {
            hi = x;
        } else {
            lo = x + 1;
        }
    }
    if (lo > m) {
        std::cout << "NO\n";
        return 0;
    }
    std::cout << "YES\n";
    for (int i = 0; i < m; i++) {
        std::cout << ans[i] + 1 << " \n"[i == m - 1];
    }
    return 0;
}
