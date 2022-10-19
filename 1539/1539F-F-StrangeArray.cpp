// url:https://codeforces.com/contest/1539/problem/F
// time:2021-06-20 14:21:38
// name:F-StrangeArray

#include <bits/stdc++.h>
using i64 = long long;
struct Info {
    int sum;
    int mxp, mxs;
    int mnp, mns;
    Info(int x = 0) : sum(x), mxp(std::max(0, x)), mxs(std::max(0, x)), mnp(std::min(0, x)), mns(std::min(0, x)) {}
};
Info merge(const Info &a, const Info &b) {
    Info res;
    res.sum = a.sum + b.sum;
    res.mxp = std::max(a.mxp, a.sum + b.mxp);
    res.mxs = std::max(b.mxs, b.sum + a.mxs);
    res.mnp = std::min(a.mnp, a.sum + b.mnp);
    res.mns = std::min(b.mns, b.sum + a.mns);
    return res;
}
struct SegmentTree {
    int n;
    std::vector<Info> info;
    SegmentTree(int n) : n(n), info(4 * n) {};
    void pull(int p) {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
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
        pull(p);
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
    Info query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return a[i] < a[j];
    });
    std::vector<int> ans(n);
    SegmentTree t(n);
    for (int i = 0; i < n; i++) {
        t.modify(i, 1);
    }
    for (int l = 0, r; l < n; l = r) {
        r = l;
        while (r < n && a[p[l]] == a[p[r]]) {
            r++;
        }
        for (int i = l; i < r; i++) {
            int j = p[i];
            ans[j] = std::max(ans[j], (t.query(0, j).mxs + t.query(j + 1, n).mxp + 1) / 2);
        }
        for (int i = l; i < r; i++) {
            int j = p[i];
            t.modify(j, -1);
        }
        for (int i = l; i < r; i++) {
            int j = p[i];
            ans[j] = std::max(ans[j], (-t.query(0, j).mns - t.query(j + 1, n).mnp) / 2);
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}
