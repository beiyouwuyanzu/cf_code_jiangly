// url:https://codeforces.com/contest/724/problem/G
// time:2021-12-23 18:38:51
// name:G-Xor-maticNumberoftheGraph

#include <bits/stdc++.h>

constexpr int P = 1E9 + 7;
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<std::pair<int, i64>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        i64 t;
        std::cin >> u >> v >> t;
        u--;
        v--;
        adj[u].emplace_back(v, t);
        adj[v].emplace_back(u, t);
    }
    
    Z ans;
    
    std::vector<i64> f(n, -1);
    std::vector<Z> pw(61);
    pw[0] = 1;
    for (int i = 1; i <= 60; i++) {
        pw[i] = pw[i - 1] * 2;
    }
    for (int s = 0; s < n; s++) {
        if (f[s] != -1) {
            continue;
        }
        std::vector<i64> b(60);
        f[s] = 0;
        
        int rank = 0;
        std::vector<bool> h(60);
        auto add = [&](auto x) {
            for (int i = 0; i < 60; i++) {
                if (x >> i & 1) {
                    h[i] = true;
                }
            }
            for (int i = 0; i < 60; i++) {
                if (x >> i & 1) {
                    if (b[i] == 0) {
                        rank++;
                        b[i] = x;
                        return;
                    } else {
                        x ^= b[i];
                    }
                }
            }
        };
        
        std::queue<int> q;
        q.push(s);
        
        std::vector<int> sum(60);
        int N = 0;
        
        while (!q.empty()) {
            int u = q.front();
            N++;
            for (int i = 0; i < 60; i++) {
                sum[i] += f[u] >> i & 1;
            }
            q.pop();
            
            for (auto [v, t] : adj[u]) {
                if (f[v] == -1) {
                    f[v] = f[u] ^ t;
                    q.push(v);
                } else {
                    add(f[v] ^ f[u] ^ t);
                }
            }
        }
        
        
        for (int i = 0; i < 60; i++) {
            if (h[i]) {
                ans += 1LL * N * (N - 1) / 2 % P * pw[rank - 1] * pw[i];
            } else {
                ans += 1LL * sum[i] * (N - sum[i]) % P * pw[rank] * pw[i];
            }
        }
    }
    
    std::cout << ans.val() << "\n";
    
    return 0;
}
