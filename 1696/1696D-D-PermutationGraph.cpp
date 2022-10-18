//url:https://codeforces.com/contest/1696/problem/D
//time:2022-06-25 20:42:47
//name:D-PermutationGraph

#include <bits/stdc++.h>

using i64 = long long;

template<class Info,
    class Merge = std::plus<Info>>
struct SegmentTree {
    const int n;
    const Merge merge;
    std::vector<Info> info;
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << std::__lg(n)) {}
    SegmentTree(std::vector<Info> init) : SegmentTree(init.size()) {
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
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
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
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};

struct Max {
    int x;
    Max(int x = 0) : x(x) {}
};

Max operator+(const Max &a, const Max &b) {
    return std::max(a.x, b.x);
}

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
        b[a[i]] = i;
    }
    
    SegmentTree<Max> seg1(n), seg2(n);
    for (int i = 0; i < n; i++) {
        seg1.modify(i, a[i]);
        seg2.modify(i, n - 1 - a[i]);
    }
    
    std::vector<int> lmn(n), rmn(n), lmx(n), rmx(n);
    std::vector<int> s;
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && a[i] < a[s.back()]) {
            s.pop_back();
        }
        rmn[i] = s.empty() ? n : s.back();
        s.push_back(i);
    }
    s = {};
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && a[i] > a[s.back()]) {
            s.pop_back();
        }
        rmx[i] = s.empty() ? n : s.back();
        s.push_back(i);
    }
    s = {};
    
    int i = 0;
    int ans = 0;
    while (i < n - 1) {
        ans++;
        if (a[i] < a[i + 1]) {
            i = b[seg1.rangeQuery(i, rmn[i]).x];
        } else {
            i = b[n - 1 - seg2.rangeQuery(i, rmx[i]).x];
        }
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

