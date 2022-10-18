//url:https://codeforces.com/contest/1555/problem/E
//time:2022-06-22 16:15:25
//name:E-BoringSegments

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

struct Min {
    int x;
    Min(int x = inf) : x(x) {}
};

Min operator+(const Min &a, const Min &b) {
    return std::min(a.x, b.x);
}

void apply(Min &a, int b) {
    a.x += b;
}

void apply(int &a, int b) {
    a += b;
}

template<class Info, class Tag,
    class Merge = std::plus<Info>>
struct LazySegmentTree {
    const int n;
    const Merge merge;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)), tag(4 << std::__lg(n)) {}
    LazySegmentTree(std::vector<Info> init) : LazySegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
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
    void apply(int p, const Tag &v) {
        ::apply(info[p], v);
        ::apply(tag[p], v);
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
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
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
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    m--;
    
    std::vector<std::array<int, 3>> range(n);
    
    for (int i = 0; i < n; i++) {
        int l, r, w;
        std::cin >> l >> r >> w;
        l--;
        r--;
        range[i] = {w, l, r};
    }
    std::sort(range.begin(), range.end());
    
    LazySegmentTree<Min, int> seg(std::vector(m, Min(0)));
    
    int ans = inf;
    
    for (int i = 0, j = 0; i < n; i++) {
        while (j < n && seg.info[1].x == 0) {
            seg.rangeApply(range[j][1], range[j][2], 1);
            j++;
        }
        
        if (seg.info[1].x > 0) {
            ans = std::min(ans, range[j - 1][0] - range[i][0]);
        }
        seg.rangeApply(range[i][1], range[i][2], -1);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}

