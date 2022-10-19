// url:https://codeforces.com/contest/1637/problem/H
// time:2022-02-12 19:37:31
// name:H-MinimizeInversionsNumber

#include <bits/stdc++.h>

using i64 = long long;

template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};

constexpr int N = 1 << 20, inf = 1E9;

std::pair<int, int> mn[N];

auto rangeMin(int p, int l, int r, int x, int y) {
    if (l >= y || r <= x) {
        return std::pair(inf, -1);
    }
    if (l >= x && r <= y) {
        return mn[p];
    }
    int m = (l + r) / 2;
    return std::min(rangeMin(2 * p, l, m, x, y), rangeMin(2 * p + 1, m, r, x, y));
}

void pull(int p) {
    mn[p] = std::min(mn[2 * p], mn[2 * p + 1]);
}

void enable(int p, int l, int r, int x) {
    if (r - l == 1) {
        mn[p] = {inf, -1};
        return;
    }
    int m = (l + r) / 2;
    if (x < m) {
        enable(2 * p, l, m, x);
    } else {
        enable(2 * p + 1, m, r, x);
    }
    pull(p);
}

void build(int p, int l, int r, auto &a) {
    if (r - l == 1) {
        mn[p] = {a[l], l};
        return;
    }
    int m = (l + r) / 2;
    build(2 * p, l, m, a);
    build(2 * p + 1, m, r, a);
    pull(p);
}

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    
    Fenwick<int> fen(n);
    
    std::vector<int> v(n);
    
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        int s = fen.rangeSum(a[i], n);
        ans += s;
        fen.add(a[i], 1);
        v[i] = i - 2 * s;
    }
    
    std::cout << ans;
    
    Fenwick<int> addv(n), addp(n);
    
    std::set<int> s{-1, n};
    
    build(1, 0, n, a);
    
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> h;
    
    a.push_back(inf);
    
    auto search = [&](auto l, auto r, int t) {
        while (true) {
            auto [x, j] = rangeMin(1, 0, n, *l + 1, *r);
            if (x >= a[*r]) {
                return;
            }
            l = s.insert(j).first;
            h.emplace(v[j] + 2 * (t - addv.rangeSum(a[j], n) - addp.sum(j)), j);
            enable(1, 0, n, j);
        }
    };
    
    search(s.begin(), std::next(s.begin()), 0);
    
    for (int i = 0; i < n; i++) {
        auto [x, j] = h.top();
        h.pop();
        ans += x - i;
        std::cout << " " << ans;
        addv.add(a[j], 1);
        addp.add(j, 1);
        auto it = s.erase(s.find(j));
        search(std::prev(it), it, i + 1);
    }
    std::cout << "\n";
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
