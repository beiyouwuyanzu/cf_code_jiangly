// url:https://codeforces.com/contest/377/problem/D
// time:2021-06-19 22:09:25
// name:D-DevelopingGame

#include <bits/stdc++.h>
using i64 = long long;
constexpr int C = 3e5;
struct SegmentTree {
    int n;
    std::vector<int> tag, mx;
    SegmentTree(int n) : n(n), tag(4 * n), mx(4 * n) {}
    void add(int p, int v) {
        tag[p] += v;
        mx[p] += v;
    }
    void push(int p) {
        add(2 * p, tag[p]);
        add(2 * p + 1, tag[p]);
        tag[p] = 0;
    }
    void pull(int p) {
        mx[p] = std::max(mx[2 * p], mx[2 * p + 1]);
    }
    void rangeAdd(int p, int l, int r, int x, int y, int v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            add(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeAdd(int l, int r, int v) {
        rangeAdd(1, 0, n, l, r, v);
    }
    int findMax(int p, int l, int r) {
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        if (mx[2 * p] > mx[2 * p + 1]) {
            return findMax(2 * p, l, m);
        } else {
            return findMax(2 * p + 1, m, r);
        }
    }
    int findMax() {
        return findMax(1, 0, n);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    SegmentTree t(C);
    std::vector<std::vector<std::tuple<int, int, int>>> events(C + 1);
    std::vector<int> l(n), v(n), r(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> v[i] >> r[i];
        l[i]--;
        v[i]--;
        r[i]--;
        events[l[i]].emplace_back(v[i], r[i], 1);
        events[v[i] + 1].emplace_back(v[i], r[i], -1);
    }
    int ans = 0;
    int X, Y;
    for (int x = 0; x < C; x++) {
        for (auto [l, r, v] : events[x]) {
            t.rangeAdd(l, r + 1, v);
        }
        if (t.mx[1] > ans) {
            X = x;
            Y = t.findMax();
            ans = t.mx[1];
        }
    }
    std::cout << ans << "\n";
    for (int i = 0; i < n; i++) {
        if (l[i] <= X && X <= v[i] && v[i] <= Y && Y <= r[i]) {
            std::cout << i + 1 << " ";
        }
    }
    std::cout << "\n";
    return 0;
}
