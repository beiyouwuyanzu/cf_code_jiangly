// url:https://codeforces.com/contest/1619/problem/H
// time:2021-12-20 18:56:54
// name:H-PermutationandQueries

#include <bits/stdc++.h>

using i64 = long long;

struct Node {
    Node *ch[2];
    Node *p;
    int v;
    int siz;
    
    Node(int v) : ch{nullptr, nullptr}, p(nullptr), v(v), siz(1) {}
    
    void pull() {
        siz = 1;
        if (ch[0] != nullptr) {
            siz += ch[0]->siz;
        }
        if (ch[1] != nullptr) {
            siz += ch[1]->siz;
        }
    }
    
    void rotate() {
        Node *q = p;
        bool x = !pos();
        q->ch[!x] = ch[x];
        if (ch[x] != nullptr) {
            ch[x]->p = q;
        }
        p = q->p;
        if (q->p != nullptr) {
            q->p->ch[q->pos()] = this;
        }
        ch[x] = q;
        q->p = this;
        q->pull();
    }
    
    bool pos() {
        return p->ch[1] == this;
    }
    
    void splay(Node *g = nullptr) {
        while (p != g) {
            if (p->p != g) {
                if (pos() == p->pos()) {
                    p->rotate();
                } else {
                    rotate();
                }
            }
            rotate();
        }
        pull();
    }
};

Node *select(Node *t, int k) {
    if (t->ch[0] != nullptr) {
        if (k < t->ch[0]->siz) {
            return select(t->ch[0], k);
        } else {
            k -= t->ch[0]->siz;
        }
    }
    if (k == 0) {
        return t;
    }
    k--;
    return select(t->ch[1], k);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
    }
    
    std::vector<Node *> nodes(n);
    
    std::vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        
        std::vector<int> v;
        for (int j = i; !vis[j]; j = p[j]) {
            v.push_back(j);
            vis[j] = true;
        }
        
        std::function<Node *(int, int)> build = [&](int l, int r) -> Node * {
            if (l > r) {
                return nullptr;
            }
            int m = (l + r) / 2;
            int u = v[m];
            nodes[u] = new Node(u);
            
            nodes[u]->ch[0] = build(l, m - 1);
            nodes[u]->ch[1] = build(m + 1, r);
            
            for (int i : {0, 1}) {
                if (nodes[u]->ch[i] != nullptr) {
                    nodes[u]->ch[i]->p = nodes[u];
                }
            }
            
            nodes[u]->pull();
            return nodes[u];
        };
        build(0, v.size() - 1);
    }
    
    while (q--) {
        int op, x, y;
        std::cin >> op >> x >> y;
        x--;
        
        if (op == 1) {
            y--;
            
            auto u = nodes[x];
            auto v = nodes[y];
            
            u->splay();
            
            auto cano = [&](auto u) {
                if (u->ch[1] != nullptr) {
                    auto rm = select(u->ch[1], 0);
                    rm->splay(u);
                    
                    u->ch[1] = nullptr;
                    rm->p = nullptr;
                    u->pull();
                    
                    auto rt = select(u, 0);
                    rt->splay();
                    
                    rt->ch[0] = rm;
                    rm->p = rt;
                    rt->pull();
                    
                    u->splay();
                }
            };
            
            cano(u);
            
            v->splay();
            
            if (u->p == nullptr) {
                cano(v);
                u->ch[1] = v;
                v->p = u;
                u->pull();
            } else {
                v->ch[1]->p = nullptr;
                v->ch[1] = nullptr;
                v->pull();
            }
        } else {
            auto u = nodes[x];
            u->splay();
            
            int s = u->siz;
            int j = u->ch[0] == nullptr ? 0 : u->ch[0]->siz;
            
            j = (j + y) % s;
            u = select(u, j);
            
            u->splay();
            std::cout << u->v + 1 << "\n";
        }
    }
    
    return 0;
}

