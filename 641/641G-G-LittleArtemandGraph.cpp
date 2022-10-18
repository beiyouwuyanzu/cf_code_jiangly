//url:https://codeforces.com/contest/641/problem/G
//time:2021-07-09 23:25:54
//name:G-LittleArtemandGraph

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    if (n == k) {
        std::cout << power(n, n - 2) << "\n";
        return 0;
    }
    
    std::vector<std::vector<int>> part;
    std::vector<int> cur(k + 1);
    std::function<void(int, int)> dfs = [&](int u, int m) {
        if (u == k + 1) {
            part.push_back(cur);
            return;
        }
        
        for (int i = 0; i <= m + 1; i++) {
            cur[u] = i;
            dfs(u + 1, std::max(i, m));
        }
    };
    dfs(0, -1);
    
    auto getId = [&](std::vector<int> p) {
        return std::lower_bound(part.begin(), part.end(), p) - part.begin();
    };
    
    int N = part.size();
    
    std::vector ae(N, std::vector(k + 1, std::vector<int>(k + 1)));
    for (int i = 0; i < N; i++) {
        for (int u = 0; u <= k; u++) {
            for (int v = 0; v <= k; v++) {
                auto p = part[i];
                
                if (p[u] == p[v]) {
                    ae[i][u][v] = -1;
                    continue;
                }
                
                int pu = p[u], pv = p[v];
                if (pu > pv) {
                    std::swap(pu, pv);
                }
                for (auto &x : p) {
                    if (x == pv) {
                        x = pu;
                    } else if (x > pv) {
                        x--;
                    }
                }
                
                ae[i][u][v] = getId(p);
            }
        }
    }

    std::vector trans(N, std::vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int cur = i;
            auto p = part[j];
            
            std::vector<int> lst(k + 1, -1);
            for (int u = 0; u <= k; u++) {
                if (lst[p[u]] >= 0) {
                    cur = ae[cur][lst[p[u]]][u];
                    
                    if (cur < 0) {
                        break;
                    }
                }
                
                lst[p[u]] = u;
            }
            
            trans[i][j] = cur;
        }
    }
    
    std::vector a(n, std::vector<int>(k));
    for (int i = k; i < n; i++) {
        for (int j = 0; j < k; j++) {
            std::cin >> a[i][j];
            a[i][j]--;
        }
        std::sort(a[i].begin(), a[i].end());
    }
    
    std::vector dp(n, std::vector<Z>(N));
    for (int i = k; i < n; i++) {
        dp[i][N - 1] = 1;
    }
    
    dp[k - 1][ae[N - 1][0][k]] = 1;
    
    for (int i = n - 1; i >= k; i--) {
        for (int j = 0; j < k; j++) {
            auto g = dp[i];
            
            for (int s = 0; s < N; s++) {
                int v = ae[s][j][k];
                if (v >= 0) {
                    g[v] += dp[i][s];
                }
            }
            
            dp[i] = g;
        }
        
        int parent = a[i].back();
        
        std::vector<Z> g(N);
        for (int s = 0; s < N; s++) {
            auto p = part[s];
            
            if (std::max_element(p.begin(), p.end()) == p.begin() + k) {
                continue;
            }
            
            if (parent >= k) {
                int j = 0, mx = -1;
                while (a[parent][j] == a[i][j]) {
                    mx = std::max(mx, p[j]);
                    j++;
                }
                
                for (int u = k; u > j; u--) {
                    p[u] = p[u - 1];
                    if (p[u] > mx) {
                        p[u]++;
                    }
                }
                
                p[j] = mx + 1;
            } else {
                p[k] = *std::max_element(p.begin(), p.begin() + k) + 1;
            }
            
            auto u = getId(p);
            
            for (int t = 0; t < N; t++) {
                int v = trans[u][t];
                if (v >= 0) {
                    g[v] += dp[i][s] * dp[parent][t];
                }
            }
        }
        
        dp[parent] = g;
    }
    
    for (int u = 0; u < k; u++) {
        for (int v = u + 1; v < k; v++) {
            auto g = dp[k - 1];
            
            for (int s = 0; s < N; s++) {
                int t = ae[s][u][v];
                if (t >= 0) {
                    g[t] += dp[k - 1][s];
                }
            }
            
            dp[k - 1] = g;
        }
    }
    
    std::cout << dp[k - 1][0].val() << "\n";
    
    return 0;
}
