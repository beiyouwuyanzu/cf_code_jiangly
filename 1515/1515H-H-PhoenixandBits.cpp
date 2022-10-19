// url:https://codeforces.com/contest/1515/problem/H
// time:2021-05-02 22:04:41
// name:H-PhoenixandBits

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
struct Node {
    int cnt;
    int type;
    int tag;
    int both;
    int d;
    Node *lc, *rc;
};
Node *null = new Node();
Node *newNode(int d) {
    Node *t = new Node();
    *t = *null;
    t->d = d;
    return t;
}
Node *merge(Node *, Node *);
void maintain(Node *);
void pull(Node *t) {
    if (t->d == 0) {
        return;
    }
    t->cnt = t->lc->cnt + t->rc->cnt;
    t->both = t->lc->both | t->rc->both;
    if (t->lc != null && t->rc != null) {
        t->both |= 1 << (t->d - 1);
    }
    maintain(t);
}
void apply(Node *t, int type, int tag) {
    if (t == null || t->d == 0) {
        return;
    }
    t->type |= type;
    t->tag |= tag & type;
    t->tag &= tag | ~type;
    t->tag ^= tag & ~type;
    maintain(t);
}
void push(Node *t) {
    if (t->type >> (t->d - 1) & 1) {
        if (t->tag >> (t->d - 1) & 1) {
            t->rc = merge(t->lc, t->rc);
            t->lc = null;
            apply(t->rc, t->type, t->tag);
        } else {
            t->lc = merge(t->lc, t->rc);
            t->rc = null;
            apply(t->lc, t->type, t->tag);
        }
    } else {
        if (t->tag >> (t->d - 1) & 1) {
            std::swap(t->lc, t->rc);
        }
        apply(t->lc, t->type, t->tag);
        apply(t->rc, t->type, t->tag);
    }
    t->type = t->tag = 0;
}
void maintain(Node *t) {
    if (t == null) {
        return;
    }
    if (!(t->both & t->type)) {
        return;
    }
    push(t);
    maintain(t->lc);
    maintain(t->rc);
    pull(t);
}
Node *merge(Node *a, Node *b) {
    if (a == null) {
        return b;
    }
    if (b == null) {
        return a;
    }
    if (a->d == 0) {
        a->cnt = a->cnt | b->cnt;
        delete b;
        return a;
    }
    push(a);
    push(b);
    a->lc = merge(a->lc, b->lc);
    a->rc = merge(a->rc, b->rc);
    delete b;
    pull(a);
    return a;
}
void add(Node *&t, int v, int d) {
    if (t == null) {
        t = newNode(d);
    }
    if (d == 0) {
        t->cnt = 1;
    } else {
        if (~v >> (d - 1) & 1) {
            add(t->lc, v, d - 1);
        } else {
            add(t->rc, v, d - 1);
        }
        pull(t);
    }
}
std::vector<std::pair<int, Node *>> nodes;
void modify1(Node *&t, int L, int R, int l, int r, int x, int type) {
    if (L >= r || R <= l) {
        return;
    }
    if (t == null) {
        return;
    }
    if (L >= l && R <= r) {
        Node *backup = t;
        t = null;
        if (type == 1) {
            apply(backup, ~x, 0);
            nodes.emplace_back(L & x, backup);
        } else if (type == 2) {
            apply(backup, x, x);
            nodes.emplace_back(L | x, backup);
        } else {
            apply(backup, 0, x);
            nodes.emplace_back(L ^ x, backup);
        }
        return;
    }
    int m = (L + R) / 2;
    push(t);
    modify1(t->lc, L, m, l, r, x, type);
    modify1(t->rc, m, R, l, r, x, type);
    pull(t);
}
void modify2(Node *&t, int l, int r, int d) {
    if (t == null) {
        t = newNode(d);
    }
    while (l < r && nodes[l].second->d == d) {
        t = merge(t, nodes[l].second);
        l++;
    }
    if (l == r) {
        return;
    }
    int mid = l;
    while (mid < r && (~nodes[mid].first >> (d - 1) & 1)) {
        mid++;
    }
    push(t);
    modify2(t->lc, l, mid, d - 1);
    modify2(t->rc, mid, r, d - 1);
    pull(t);
}
int query(Node *t, int L, int R, int l, int r) {
    if (t == null) {
        return 0;
    }
    if (L >= r || R <= l) {
        return 0;
    }
    if (L >= l && R <= r) {
        return t->cnt;
    }
    int m = (L + R) / 2;
    push(t);
    return query(t->lc, L, m, l, r) + query(t->rc, m, R, l, r);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    null->cnt = null->type = null->tag = null->both = 0;
    null->lc = null->rc = null;
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    Node *root = null;
    for (int i = 0; i < n; i++) {
        add(root, a[i], 20);
    }
    while (q--) {
        int op, l, r, x;
        std::cin >> op >> l >> r;
        r++;
        if (op <= 3) {
            std::cin >> x;
            modify1(root, 0, 1 << 20, l, r, x, op);
            std::sort(nodes.begin(), nodes.end(), [&](const auto &a, const auto &b) {
                int va = a.first & ~((1 << a.second->d) - 1);
                int vb = b.first & ~((1 << b.second->d) - 1);
                if (va != vb) {
                    return va < vb;
                }
                return a.second->d > b.second->d;
            });
            modify2(root, 0, nodes.size(), 20);
            nodes.clear();
        } else {
            std::cout << query(root, 0, 1 << 20, l, r) << "\n";
        }
    }
    return 0;
}
