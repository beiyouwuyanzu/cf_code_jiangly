// url:https://codeforces.com/contest/609/problem/F
// time:2023-04-24 09:03:00
// name:F-Frogsandmosquitoes

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

constexpr int inf = 1E9+1;
struct Min {
    int x = inf;
    void apply(Min t) & {
        x = std::min(x, t.x);
    }
};
Min operator+(Min a, Min b) {
    return {std::min(a.x, b.x)};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> x(n);
    std::vector<i64> t(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> t[i];
    }
    std::vector<int> o(n);
    std::iota(o.begin(), o.end(), 0);
    std::sort(o.begin(), o.end(), [&](int i, int j) {
        return x[i] < x[j];
    });
    
    std::vector<int> p(m), s(m);
    for (int i = 0; i < m; i++) {
        std::cin >> p[i] >> s[i];
    }
    auto vp = p;
    std::sort(vp.begin(), vp.end());
    LazySegmentTree<Min, Min> seg(m);
    for (int i = 0; i < n; i++) {
        int j = o[i];
        int l = std::lower_bound(vp.begin(), vp.end(), x[j]) - vp.begin();
        int r = std::lower_bound(vp.begin(), vp.end(), x[j]+t[j]+1) - vp.begin();
        seg.rangeApply(l, r, {i});
    }
    
    std::vector<int> cnt(n);
    
    std::multiset<std::pair<int, int>> S;
    for (int i = 0; i < m; i++) {
        int q = std::lower_bound(vp.begin(), vp.end(), p[i]) - vp.begin();
        
        int k = seg.rangeQuery(q, q+1).x;
        if (k == inf) {
            S.emplace(p[i], s[i]);
            continue;
        }
        
        int j = o[k];
        cnt[j] += 1;
        t[j] += s[i];
        auto it = S.lower_bound({x[j], 0});
        while (it != S.end() && it->first <= x[j] + t[j]) {
            cnt[j]++;
            t[j] += it->second;
            it = S.erase(it);
        }
        int l = std::lower_bound(vp.begin(), vp.end(), x[j]) - vp.begin();
        int r = std::lower_bound(vp.begin(), vp.end(), x[j]+t[j]+1) - vp.begin();
        seg.rangeApply(l, r, {k});
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << cnt[i] << " " << t[i] << "\n";
    }
    
    return 0;
}
