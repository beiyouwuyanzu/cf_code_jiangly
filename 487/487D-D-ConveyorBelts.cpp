// url:https://codeforces.com/contest/487/problem/D
// time:2021-06-24 21:29:04
// name:D-ConveyorBelts

#include <bits/stdc++.h>
using i64 = long long;
struct Info {
    std::vector<std::pair<int, int>> a;
    Info() {}
    Info(int r, const std::string &s) {
        int m = s.size();
        a.assign(m, {-2, -2});
        for (int i = 0; i < m; i++) {
            if (s[i] == '^') {
                a[i] = {r - 1, i};
            } else if (s[i] == '<') {
                if (i == 0) {
                    a[i] = {r, -1};
                } else {
                    a[i] = a[i - 1];
                }
            } else {
                if (i == m - 1) {
                    a[i] = {r, m};
                } else {
                    a[i] = a[i + 1];
                }
            }
        }
        for (int i = m - 1; i >= 0; i--) {
            if (s[i] == '^') {
                a[i] = {r - 1, i};
            } else if (s[i] == '<') {
                if (i == 0) {
                    a[i] = {r, -1};
                } else {
                    a[i] = a[i - 1];
                }
            } else {
                if (i == m - 1) {
                    a[i] = {r, m};
                } else {
                    a[i] = a[i + 1];
                }
            }
        }
    }
};
Info merge(const Info &a, const Info &b) {
    Info c;
    int m = a.a.size();
    c.a.resize(m);
    for (int i = 0; i < m; i++) {
        if (b.a[i].second < 0 || b.a[i].second >= m) {
            c.a[i] = b.a[i];
        } else {
            c.a[i] = a.a[b.a[i].second];
        }
    }
    return c;
}
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree(const std::vector<std::string> &s) {
        n = s.size();
        info.resize(4 * n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = Info(l, s[l]);
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void modify(int p, int l, int r, int x, const std::string &s) {
        if (r - l == 1) {
            info[p] = Info(l, s);
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, s);
        } else {
            modify(2 * p + 1, m, r, x, s);
        }
        pull(p);
    }
    void modify(int x, const std::string &s) {
        modify(1, 0, n, x, s);
    }
    void query(int p, int l, int r, int x, std::pair<int, int> &res) {
        if (l >= x + 1) {
            return;
        }
        if (r <= x + 1) {
            if (0 <= res.second && res.second < int(info[p].a.size())) {
                res = info[p].a[res.second];
            }
            return;
        }
        int m = (l + r) / 2;
        query(2 * p + 1, m, r, x, res);
        query(2 * p, l, m, x, res);
    }
    std::pair<int, int> query(int x, int y) {
        std::pair<int, int> res{x, y};
        query(1, 0, n, x, res);
        return res;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    SegmentTree t(s);
    while (q--) {
        char op;
        int x, y;
        std::cin >> op >> x >> y;
        x--;
        y--;
        if (op == 'A') {
            auto [u, v] = t.query(x, y);
            std::cout << u + 1 << " " << v + 1 << "\n";
        } else {
            std::cin >> s[x][y];
            t.modify(x, s[x]);
        }
    }
    return 0;
}
