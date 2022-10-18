//url:https://codeforces.com/contest/702/problem/F
//time:2021-07-12 20:24:00
//name:F-T-Shirts

#include <bits/stdc++.h>

using i64 = long long;
using u32 = unsigned;

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l;
    Node *r;
    int s;
    int t;
    int a;
    int g;
    u32 w;
    
    Node(int s) : l(nullptr), r(nullptr), s(s), t(0), a(0), g(0), w(rnd()) {}
    
    void apply(int vt, int vg) {
        s -= vt;
        t += vt;
        a += vg;
        g += vg;
    }
    
    void push() {
        if (l != nullptr) {
            l->apply(t, g);
        }
        if (r != nullptr) {
            r->apply(t, g);
        }
        
        t = g = 0;
    }
};

std::pair<Node *, Node *> split(Node *t, int v) {
    if (t == nullptr) {
        return {nullptr, nullptr};
    }
    
    t->push();
    if (t->s < v) {
        auto [x, y] = split(t->r, v);
        t->r = x;
        return {t, y};
    } else {
        auto [x, y] = split(t->l, v);
        t->l = y;
        return {x, t};
    }
}

Node *merge(Node *p, Node *q) {
    if (p == nullptr) {
        return q;
    }
    if (q == nullptr) {
        return p;
    }
    
    if (p->w < q->w) {
        std::swap(p, q);
    }
    
    auto [x, y] = split(q, p->s + rnd() % 2);
    
    p->push();
    p->l = merge(p->l, x);
    p->r = merge(p->r, y);
    
    return p;
}

void dfs(Node *t) {
    if (t == nullptr) {
        return;
    }
    
    t->push();
    dfs(t->l);
    dfs(t->r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> c(n), q(n);
    for (int i = 0; i < n; i++) {
        std::cin >> c[i] >> q[i];
    }
    
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        if (q[i] != q[j]) {
            return q[i] > q[j];
        } else {
            return c[i] < c[j];
        }
    });
    
    int m;
    std::cin >> m;
    
    Node *t = nullptr;
    
    std::vector<Node *> node(m);
    for (int i = 0; i < m; i++) {
        int s;
        std::cin >> s;
        node[i] = new Node(s);
        t = merge(t, node[i]);
    }
    
    for (auto i : p) {
        auto [x, y] = split(t, c[i]);
        
        if (y != nullptr) {
            y->apply(c[i], 1);
        }
        
        t = merge(x, y);
    }
    
    dfs(t);
    
    for (int i = 0; i < m; i++) {
        std::cout << node[i]->a << " \n"[i == m - 1];
    }
    
    return 0;
}
