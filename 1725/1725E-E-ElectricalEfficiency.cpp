//url:https://codeforces.com/contest/1725/problem/E
//time:2022-09-04 18:42:01
//name:E-ElectricalEfficiency

#include <bits/stdc++.h>

using i64 = long long;
struct Tree {
    int n;
    std::vector<int> siz, top, dep, parent, in, out;
    std::vector<std::vector<int>> adj;
    Tree(int n) : n(n), siz(n), top(n), dep(n), parent(n, -1), in(n), out(n), adj(n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void init(int root = 0) {
        top[root] = root;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (parent[u] != -1) {
            adj[u].erase(std::find(adj[u].begin(), adj[u].end(), parent[u]));
        }
        
        siz[u] = 1;
        for (auto &v : adj[u]) {
            parent[v] = u;
            dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                std::swap(v, adj[u][0]);
            }
        }
    }
    int cur = 0;
    void dfs2(int u) {
        in[u] = cur++;
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = parent[top[u]];
            } else {
                v = parent[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
};
constexpr int P = 998244353;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    Z(i64 x) : x(norm(x % P)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        i64 v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    int m = 0;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        m = std::max(m, a[i]);
    }
    
    std::vector<int> minp(m + 1);
    std::vector<int> primes;
    
    for (int i = 2; i <= m; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > m) {
                break;
            }
            minp[i * p] = p;
            if (i % p == 0) {
                break;
            }
        }
    }
    
    Tree tree(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        tree.addEdge(u, v);
    }
    tree.init();
    
    std::vector<std::vector<int>> p(m + 1);
    for (int i = 0; i < n; i++) {
        for (int x = a[i]; x > 1; ) {
            int q = minp[x];
            p[q].push_back(i);
            while (x % q == 0) {
                x /= q;
            }
        }
    }
    
    Z ans = 0;
    
    std::vector<int> parent(n, -1), siz(n);
    
    for (int x = 1; x <= m; x++) {
        if (p[x].size() < 3) {
            continue;
        }
        
        const int s = p[x].size();
        auto a = p[x];
        std::sort(a.begin(), a.end(), [&](int i, int j) {
            return tree.in[i] < tree.in[j];
        });
        for (int i = int(a.size()) - 2; i >= 0; i--) {
            a.push_back(tree.lca(a[i], a[i + 1]));
        }
        
        std::sort(a.begin(), a.end(), [&](int i, int j) {
            return tree.in[i] < tree.in[j];
        });
        a.erase(std::unique(a.begin(), a.end()), a.end());
        
        std::vector<int> stk{a[0]};
        for (int i = 1; i < int(a.size()); i++) {
            while (tree.in[a[i]] >= tree.out[stk.back()]) {
                stk.pop_back();
            }
            parent[a[i]] = stk.back();
            stk.push_back(a[i]);
        }
        
        for (auto u : a) {
            siz[u] = 0;
        }
        for (auto u : p[x]) {
            siz[u] = 1;
        }
        
        for (int i = a.size() - 1; i > 0; i--) {
            siz[parent[a[i]]] += siz[a[i]];
            ans += Z(siz[a[i]]) * (s - siz[a[i]]) * (s - 2) * (tree.dep[a[i]] - tree.dep[parent[a[i]]]);
        }
    }
    
    ans /= 2;
    std::cout << ans << "\n";
    
    return 0;
}
