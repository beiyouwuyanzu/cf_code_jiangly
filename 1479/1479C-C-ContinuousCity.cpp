// url:https://codeforces.com/contest/1479/problem/C
// time:2021-02-07 18:41:50
// name:C-ContinuousCity

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int L, R;
    std::cin >> L >> R;
    std::vector<std::tuple<int, int, int>> edges;
    int n = R - L + 1;
    int cur = 0;
    int m = std::__lg(2 * n - 1);
    std::vector<int> f(m + 2);
    edges.emplace_back(0, 1, L);
    cur++;
    f[cur] = 1;
    for (int i = 2; i <= 1 + m; i++) {
        int r = ((n - 1) >> (m + 1 - i)) + 1;
        f[i] = r;
        edges.emplace_back(0, i, L);
        for (int j = i - 1; j > 0; j--) {
            if (r - 1 >= f[j]) {
                r -= f[j];
                edges.emplace_back(j, i, r);
            }
        }
        assert(r == 1);
    }
    std::cout << "YES\n";
    std::cout << m + 2 << " " << edges.size() << "\n";
    for (auto [u, v, w] : edges) {
        std::cout << u + 1 << " " << v + 1 << " " << w << "\n";
    }
    return 0;
}
