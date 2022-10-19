// url:https://codeforces.com/contest/494/problem/D
// time:2021-06-21 19:05:29
// name:D-Birthday

#include <bits/stdc++.h>
constexpr int P = 1000000007;
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
T power(T a, int b) {
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
};
struct Info {
    Z a[3];
    Info() : a{} {}
    Info(int x) : a{1, x, i64(x) * (x - 1) / 2 % P} {} 
    Info &operator+=(const Info &rhs) {
        for (int i = 0; i < 3; i++) {
            a[i] += rhs.a[i];
        }
        return *this;
    }
    friend Info operator+(const Info &a, const Info &b) {
        Info c = a;
        c += b;
        return c;
    }
    Info &operator-=(const Info &rhs) {
        for (int i = 0; i < 3; i++) {
            a[i] -= rhs.a[i];
        }
        return *this;
    }
    friend Info operator-(const Info &a, const Info &b) {
        Info c = a;
        c -= b;
        return c;
    }
    friend Info operator*(const Info &a, const Info &b) {
        Info c;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; i + j < 3; j++) {
                c.a[i + j] += a.a[i] * b.a[j];
            }
        }
        return c;
    }
    Z get() const {
        return a[2] * 2 + a[1];
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::vector<std::pair<int, int>>> e(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--;
        v--;
        e[u].emplace_back(v, w);
        e[v].emplace_back(u, w);
    }
    const int lg = std::__lg(n);
    std::vector parent(n, std::vector(lg + 1, -1));
    std::vector<int> dep(n);
    std::vector<Z> dis(n);
    std::vector<Info> dp(n), sum(n), sum1(n);
    std::function<void(int)> dfs1 = [&](int u) {
        for (int j = 0; (1 << (j + 1)) <= dep[u]; j++) {
            parent[u][j + 1] = parent[parent[u][j]][j];
        }
        dp[u] = Info(0);
        for (auto [v, w] : e[u]) {
            if (v == parent[u][0]) {
                continue;
            }
            dep[v] = dep[u] + 1;
            dis[v] = dis[u] + w;
            parent[v][0] = u;
            dfs1(v);
            dp[u] += dp[v] * Info(w);
        }
    };
    std::function<void(int)> dfs2 = [&](int u) {
        sum[u] += dp[u];
        for (auto [v, w] : e[u]) {
            if (v == parent[u][0]) {
                continue;
            }
            sum[v] = sum[u] * Info(w);
            sum1[v] = sum1[u] * Info(w) + dp[v] * Info(2 * w);
            dfs2(v);
        }
    };
    dfs1(0);
    dfs2(0);
    auto lca = [&](int u, int v) {
        if (dep[u] < dep[v]) {
            std::swap(u, v);
        }
        for (int i = lg; i >= 0; i--) {
            if (dep[u] - (1 << i) >= dep[v]) {
                u = parent[u][i];
            }
        }
        if (u == v) {
            return u;
        }
        for (int i = lg; i >= 0; i--) {
            if (parent[u][i] != parent[v][i]) {
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        return parent[u][0];
    };
    std::function<Z(int, int)> query = [&](int u, int v) {
        int l = lca(u, v);
        Z subt;
        if (l == v) {
            Info res = sum[u];
            if (v) {
                res -= sum[parent[v][0]] * Info((dis[u] - dis[parent[v][0]]).val());
            }
            res -= (sum1[u] - sum1[v] * Info((dis[u] - dis[v]).val()));
            subt = res.get();
        } else {
            subt = (dp[v] * Info((dis[u] + dis[v] - 2 * dis[l]).val())).get();
        }
        Z ans;
        if (v == 0) {
            ans = subt;
        } else {
            ans = 2 * subt - query(u, 0);
        }
        return ans;
    };
    int q;
    std::cin >> q;
    while (q--) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        std::cout << query(u, v).val() << "\n";
    }
    return 0;
}
