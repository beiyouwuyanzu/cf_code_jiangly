// url:https://codeforces.com/contest/494/problem/E
// time:2021-06-21 12:01:20
// name:E-Sharti

#include <bits/stdc++.h>
using i64 = long long;
std::vector<int> val;
struct SegmentTree {
    int n;
    std::vector<int> tag, sum;
    SegmentTree(int n) : n(n), tag(4 * n), sum(4 * n) {}
    void pull(int p, int l, int r) {
        if (tag[p]) {
            sum[p] = val[r] ^ val[l];
        } else if (r - l > 1) {
            sum[p] = sum[2 * p] ^ sum[2 * p + 1];
        } else {
            sum[p] = 0;
        }
    }
    void add(int p, int l, int r, int v) {
        tag[p] += v;
        pull(p, l, r);
    }
    void rangeAdd(int p, int l, int r, int x, int y, int v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            add(p, l, r, v);
            return;
        }
        int m = (l + r) / 2;
        rangeAdd(2 * p, l, m, x, y, v);
        rangeAdd(2 * p + 1, m, r, x, y, v);
        pull(p, l, r);
    }
    void rangeAdd(int l, int r, int v) {
        rangeAdd(1, 0, n, l, r, v);
    }
    int get() {
        if (n == 0) {
            return 0;
        }
        return sum[1];
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, k;
    std::cin >> n >> m >> k;
    int u = std::__lg(k);
    std::vector<std::tuple<int, int, int, int>> events;
    for (int i = 0; i < m; i++) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        a--;
        b--;
        events.emplace_back(a, b, d, 1);
        events.emplace_back(c, b, d, -1);
        val.push_back(b);
        val.push_back(d);
    }
    std::sort(events.begin(), events.end());
    int sum = 0;
    int last = 0;
    std::sort(val.begin(), val.end());
    val.erase(std::unique(val.begin(), val.end()), val.end());
    SegmentTree t(val.size() - 1);
    for (auto [x, y1, y2, o] : events) {
        int l = std::lower_bound(val.begin(), val.end(), y1) - val.begin();
        int r = std::lower_bound(val.begin(), val.end(), y2) - val.begin();
        sum ^= t.get() & (x ^ last);
        last = x;
        t.rangeAdd(l, r, o);
    }
    if (sum & ((1 << (u + 1)) - 1)) {
        std::cout << "Hamed\n";
    } else {
        std::cout << "Malek\n";
    }
    return 0;
}
