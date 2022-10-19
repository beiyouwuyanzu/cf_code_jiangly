// url:https://codeforces.com/contest/500/problem/E
// time:2021-06-22 17:59:03
// name:E-NewYearDomino

#include <bits/stdc++.h>
struct Tag {
    int add = 0;
    int coef = 0;
    int ass = -1;
    void apply(const Tag &a) {
        if (ass == -1) {
            add += a.add;
            coef += a.coef;
        } else {
            add += a.add + a.coef * ass;
        }
        if (a.ass != -1) {
            ass = a.ass;
        }
    }
};
struct Info {
    int mn = 0;
    void apply(const Tag &v) {
        if (v.ass != -1) {
            mn = v.ass;
        }
    }
};
Info merge(const Info &a, const Info &b) {
    Info c;
    c.mn = std::min(a.mn, b.mn);
    return c;
}
struct SegmentTree {
    int n;
    std::vector<Tag> tag;
    std::vector<Info> info;
    SegmentTree(int n) : n(n), tag(4 * n), info(4 * n) {}
    void apply(int p, const Tag &v) {
        tag[p].apply(v);
        info[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void rangeModify(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeModify(2 * p, l, m, x, y, v);
        rangeModify(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeAssign(int l, int r, int v) {
        rangeModify(1, 0, n, l, r, Tag{0, 0, v});
    }
    void rangeAdd(int l, int r, int v) {
        rangeModify(1, 0, n, l, r, Tag{v, -1, -1});
    }
    int find(int p, int l, int r, int x) {
        if (info[p].mn > x) {
            return n;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = find(2 * p, l, m, x);
        if (res == n) {
            res = find(2 * p + 1, m, r, x);
        }
        return res;
    }
    int find(int x) {
        return find(1, 0, n, x);
    }
    int query(int p, int l, int r, int x) {
        if (r - l == 1) {
            return tag[p].add;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            return query(2 * p, l, m, x);
        } else {
            return query(2 * p + 1, m, r, x);
        }
    }
    int query(int x) {
        return query(1, 0, n, x);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> p(n), l(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i] >> l[i];
    }
    int q;
    std::cin >> q;
    std::vector<std::tuple<int, int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;
        queries[i] = {y, x, i};
    }
    std::sort(queries.begin(), queries.end());
    SegmentTree t(n);
    std::vector<int> ans(q);
    for (int i = 0, j = 0; i < n; i++) {
        int x = t.find(p[i]);
        t.rangeAdd(x, i, p[i]);
        x = t.find(p[i] + l[i]);
        t.rangeAssign(x, i + 1, p[i] + l[i]);
        while (j < q && std::get<0>(queries[j]) == i) {
            auto [y, x, k] = queries[j++];
            ans[k] = t.query(x);
        }
    }
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    return 0;
}
