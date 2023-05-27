// url:https://codeforces.com/contest/44/problem/G
// time:2023-04-23 12:29:23
// name:G-ShootingGallery

#include <bits/stdc++.h>

using i64 = long long;

constexpr int inf = 1E9;

struct Node {
    Node *l = nullptr;
    Node *r = nullptr;
    int xl = inf;
    int xr = -inf;
    int yl = inf;
    int yr = -inf;
    int minz = inf;
};

std::map<std::pair<int, int>, std::vector<int>> shoots;

void pull(Node *t) {
    t->minz = std::min(t->l->minz, t->r->minz);
}

Node *build(std::vector<std::array<int, 2>> pts, int lvl = 0) {
    Node *t = new Node;
    for (auto [x, y] : pts) {
        t->xl = std::min(t->xl, x);
        t->xr = std::max(t->xr, x);
        t->yl = std::min(t->yl, y);
        t->yr = std::max(t->yr, y);
    }
    if (pts.size() == 1) {
        auto [x, y] = pts[0];
        t->minz = shoots[{x, y}].back();
        return t;
    }
    int n = pts.size();
    std::nth_element(pts.begin(), pts.begin() + n/2, pts.end(), [&](auto a, auto b) {
        return a[lvl] < b[lvl];
    });
    t->l = build(std::vector(pts.begin(), pts.begin() + n/2), lvl^1);
    t->r = build(std::vector(pts.begin() + n/2, pts.end()), lvl^1);
    pull(t);
    return t;
}

int query(Node *t, int xl, int xr, int yl, int yr) {
    if (xl > t->xr || xr < t->xl || yl > t->yr || yr < t->yl) {
        return inf;
    }
    if (xl <= t->xl && xr >= t->xr && yl <= t->yl && yr >= t->yr) {
        return t->minz;
    }
    return std::min(query(t->l, xl, xr, yl, yr), query(t->r, xl, xr, yl, yr));
}

void del(Node *t, int x, int y) {
    if (x > t->xr || x < t->xl || y > t->yr || y < t->yl) {
        return;
    }
    if (x <= t->xl && x >= t->xr && y <= t->yl && y >= t->yr) {
        auto &v = shoots[{x, y}];
        v.pop_back();
        t->minz = v.empty() ? inf : v.back();
        return;
    }
    del(t->l, x, y);
    del(t->r, x, y);
    pull(t);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> xl(n), xr(n), yl(n), yr(n), z(n);
    for (int i = 0; i < n; i++) {
        std::cin >> xl[i] >> xr[i] >> yl[i] >> yr[i] >> z[i];
    }
    
    int m;
    std::cin >> m;
    
    std::vector<std::array<int, 2>> pts(m);
    std::vector<int> x(m), y(m);
    for (int i = 0; i < m; i++) {
        std::cin >> x[i] >> y[i];
        pts[i] = {x[i], y[i]};
    }
    std::sort(pts.begin(), pts.end());
    pts.erase(std::unique(pts.begin(), pts.end()), pts.end());
    
    for (int i = m-1; i >= 0; i--) {
        shoots[{x[i], y[i]}].push_back(i);
    }
    
    auto root = build(pts);
    
    std::vector<int> invz(n);
    std::iota(invz.begin(), invz.end(), 0);
    std::sort(invz.begin(), invz.end(), [&](int i, int j) {
        return z[i] < z[j];
    });
    
    std::vector<int> ans(m);
    for (int i = 0; i < n; i++) {
        int j = invz[i];
        int k = query(root, xl[j], xr[j], yl[j], yr[j]);
        if (k != inf) {
            ans[k] = j+1;
            del(root, x[k], y[k]);
        }
    }
    
    for (auto x : ans) {
        std::cout << x << "\n";
    }
    
    return 0;
}
