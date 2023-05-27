// url:https://codeforces.com/contest/280/problem/D
// time:2023-04-30 10:17:23
// name:D-k-MaximumSubsequenceSum

#include <bits/stdc++.h>

using i64 = long long;
template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    LazySegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
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
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l >= y || r <= x || !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findLast(2 * p + 1, m, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n, l, r, pred);
    }
};

struct Tag {
    int mul = 1;
    void apply(Tag t) & {
        mul *= t.mul;
    }
};

struct Info {
    std::array<int, 2> pre[2];
    std::array<int, 2> suf[2];
    std::array<int, 3> ans[2];
    int sum[2];
    
    Info() {
        pre[0] = pre[1] = {-1, -1};
        suf[0] = suf[1] = {-1, -1};
        ans[0] = ans[1] = {-1, -1, -1};
        sum[0] = sum[1] = 0;
    }
    
    Info(int i, int a) {
        for (int t = 0; t < 2; t++) {
            int v = t ? -a : a;
            if (v > 0) {
                pre[t] = {v, i + 1};
                suf[t] = {v, i};
                ans[t] = {v, i, i + 1};
            } else {
                pre[t] = {0, i};
                suf[t] = {0, i + 1};
                ans[t] = {0, i, i};
            }
            sum[t] = v;
        }
    }
    
    void apply(Tag t) & {
        if (t.mul == -1) {
            std::swap(pre[0], pre[1]);
            std::swap(suf[0], suf[1]);
            std::swap(ans[0], ans[1]);
            std::swap(sum[0], sum[1]);
        }
    }
};

Info operator+(Info a, Info b) {
    Info c;
    for (int t = 0; t < 2; t++) {
        c.sum[t] = a.sum[t] + b.sum[t];
        c.pre[t] = std::max(a.pre[t], std::array{b.pre[t][0] + a.sum[t], b.pre[t][1]});
        c.suf[t] = std::max(b.suf[t], std::array{a.suf[t][0] + b.sum[t], a.suf[t][1]});
        c.ans[t] = std::max({a.ans[t], b.ans[t], std::array{a.suf[t][0] + b.pre[t][0], a.suf[t][1], b.pre[t][1]}});
    }
    return c;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    LazySegmentTree<Info, Tag> seg(n);
    for (int i = 0; i < n; i++) {
        seg.modify(i, Info(i, a[i]));
    }
    
    int m;
    std::cin >> m;
    
    while (m--) {
        int t;
        std::cin >> t;
        
        if (t == 0) {
            int i, val;
            std::cin >> i >> val;
            i--;
            seg.modify(i, Info(i, val));
        } else {
            int l, r, k;
            std::cin >> l >> r >> k;
            l--;
            
            std::vector<std::pair<int, int>> a;
            int ans = 0;
            for (int i = 0; i < k; i++) {
                auto res = seg.rangeQuery(l, r).ans[0];
                if (res[0] <= 0) {
                    break;
                }
                ans += res[0];
                a.emplace_back(res[1], res[2]);
                seg.rangeApply(res[1], res[2], {-1});
            }
            std::cout << ans << "\n";
            for (auto [l, r] : a) {
                seg.rangeApply(l, r, {-1});
            }
        }
    }
    
    return 0;
}
