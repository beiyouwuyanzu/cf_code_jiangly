// url:https://codeforces.com/contest/498/problem/D
// time:2021-06-21 21:58:58
// name:D-TrafficJamsintheLand

#include <bits/stdc++.h>
struct Info {
    int f[60];
    Info() {
        for (int i = 0; i < 60; i++) {
            f[i] = i;
        }
    }
    Info(int a) {
        for (int i = 0; i < 60; i++) {
            f[i] = i + 1 + (i % a == 0);
        }
    }
    friend Info merge(const Info &a, const Info &b) {
        Info c;
        for (int i = 0; i < 60; i++) {
            c.f[i] = b.f[a.f[i] % 60] + a.f[i] - a.f[i] % 60;
        }
        return c;
    }
};
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree(int n) : n(n), info(4 * n) {}
    void modify(int p, int l, int r, int pos, int v) {
        if (r - l == 1) {
            info[p] = Info(v);
            return;
        }
        int m = (l + r) / 2;
        if (pos < m) {
            modify(2 * p, l, m, pos, v);
        } else {
            modify(2 * p + 1, m, r, pos, v);
        }
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void modify(int pos, int v) {
        modify(1, 0, n, pos, v);
    }
    Info query(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        return merge(query(2 * p, l, m, x, y), query(2 * p + 1, m, r, x, y));
    }
    int query(int l, int r) {
        return query(1, 0, n, l, r).f[0];
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    SegmentTree t(n);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        t.modify(i, x);
    }
    int q;
    std::cin >> q;
    while (q--) {
        char op;
        int x, y;
        std::cin >> op >> x >> y;
        if (op == 'A') {
            x--;
            y--;
            std::cout << t.query(x, y) << "\n";
        } else {
            x--;
            t.modify(x, y);
        }
    }
    return 0;
}
