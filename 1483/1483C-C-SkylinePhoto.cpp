//url:https://codeforces.com/contest/1483/problem/C
//time:2021-03-21 16:52:04
//name:C-SkylinePhoto

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr i64 inf = 1e18;
struct SegmentTree {
    std::vector<i64> mx, tag;
    SegmentTree(int n) : mx(4 * n, -inf), tag(4 * n, -inf) {}
    void push(int p) {
        maxEq(2 * p, tag[p]);
        maxEq(2 * p + 1, tag[p]);
        tag[p] = -inf;
    }
    void maxEq(int p, i64 v) {
        mx[p] = std::max(mx[p], v);
        tag[p] = std::max(tag[p], v);
    }
    void pull(int p) {
        mx[p] = std::max(mx[2 * p], mx[2 * p + 1]);
    }
    i64 rangeMax(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return -inf;
        }
        if (l >= x && r <= y) {
            return mx[p];
        }
        int m = (l + r) / 2;
        push(p);
        return std::max(rangeMax(2 * p, l, m, x, y), rangeMax(2 * p + 1, m, r, x, y));
    }
    void rangeMaxEq(int p, int l, int r, int x, int y, i64 v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            return maxEq(p, v);
        }
        int m = (l + r) / 2;
        push(p);
        rangeMaxEq(2 * p, l, m, x, y, v);
        rangeMaxEq(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> h(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    std::vector<int> lc(n, -1), rc(n, -1);
    std::vector<int> stk;
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && h[i] < h[stk.back()]) {
            rc[stk.back()] = lc[i];
            lc[i] = stk.back();
            stk.pop_back();
        }
        stk.push_back(i);
    }
    while (stk.size() > 1) {
        int x = stk.back();
        stk.pop_back();
        rc[stk.back()] = x;
    }
    SegmentTree t(n + 1);
    std::function<void(int, int, int)> solve = [&](int x, int l, int r) {
        if (x == -1) {
            return;
        }
        solve(lc[x], l, x);
        i64 v = t.rangeMax(1, 0, n + 1, l, x + 1);
        t.rangeMaxEq(1, 0, n + 1, x + 1, r + 1, v + b[x]);
        solve(rc[x], x + 1, r);
    };
    t.rangeMaxEq(1, 0, n + 1, 0, 1, 0);
    solve(stk[0], 0, n);
    std::cout << t.rangeMax(1, 0, n + 1, n, n + 1) << "\n";
    return 0;
}

