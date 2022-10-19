// url:https://codeforces.com/contest/1477/problem/C
// time:2021-01-28 18:01:00
// name:C-NezzarandNiceBeatmap

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using Point = std::complex<i64>;
i64 dot(const Point &a, const Point &b) {
    return (std::conj(a) * b).real();
}
i64 dist(const Point &a, const Point &b) {
    return dot(a - b, a - b);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Point> p(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        p[i] = Point(x, y);
    }
    std::vector<bool> vis(n);
    vis[0] = true;
    std::vector<int> a{0};
    for (int t = 1; t < n; t++) {
        i64 dis = 0;
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (vis[i]) {
                continue;
            }
            if ((t == 1 || dot(p[i] - p[a[t - 1]], p[a[t - 2]] - p[a[t - 1]]) > 0) && dist(p[i], p[a[t - 1]]) > dis) {
                dis = dist(p[i], p[a[t - 1]]);
                u = i;
            }
        }
        vis[u] = true;
        a.push_back(u);
    }
    for (int i = 0; i < n; i++) {
        std::cout << a[i] + 1 << " \n"[i == n - 1];
    }
    return 0;
}
