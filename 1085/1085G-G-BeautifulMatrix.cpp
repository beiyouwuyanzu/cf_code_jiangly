//url:https://codeforces.com/contest/1085/problem/G
//time:2021-07-15 20:00:01
//name:G-BeautifulMatrix

#include <bits/stdc++.h>


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

struct DSU {
    std::vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector a(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
            a[i][j]--;
        }
    }
    
    std::vector<Z> fac(n + 1), g(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
    }
    g[0] = 1;
    g[1] = 0;
    for (int i = 2; i <= n; i++) {
        g[i] = (i - 1) * (g[i - 1] + g[i - 2]);
    }
    
    std::vector f(n + 1, std::vector<Z>(n + 1));
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n - i; j++) {
            if (i == 0) {
                f[i][j] = fac[j];
            } else {
                if (i > 1) {
                    f[i][j] += (i - 1) * f[i - 2][j + 1];
                }
                f[i][j] += j * f[i - 1][j];
            }
        }
    }
    
    Z ans = 0;
    
    for (int i = 0; i < n; i++) {
        ans *= g[n];
        
        Fenwick<int> fi(n), fc(n);
        for (int j = 0; j < n; j++) {
            fi.add(j, 1);
        }
        
        if (i == 0) {
            for (int j = 0; j < n; j++) {
                ans += fi.sum(a[i][j]) * fac[n - j - 1];
                fi.add(a[i][j], -1);
            }
            continue;
        }
        
        DSU g(n);
        
        for (int j = 0; j < n; j++) {
            int iso = fi.sum(n);
            int chain = fc.sum(n);
            
            int type = (g.size(a[i - 1][j]) == 1 ? 0 : 1);
            
            if (type == 0) {
                iso--;
            } else {
                chain--;
            }
            
            ans += f[iso][chain] * fc.sum(a[i][j]);
            if (iso > 0) {
                ans += f[iso - 1][chain + 1] * fi.sum(a[i][j]);
            }
            
            if (g.leader(a[i - 1][j]) < a[i][j] && type == 0 && iso > 0) {
                ans -= f[iso - 1][chain + 1];
            }
            
            if (type == 0) {
                fi.add(a[i - 1][j], -1);
            } else {
                fc.add(g.leader(a[i - 1][j]), -1);
            }
            
            if (g.size(a[i][j]) == 1) {
                fi.add(a[i][j], -1);
            } else if (!g.same(a[i][j], a[i - 1][j])) {
                fc.add(a[i][j], -1);
            }
            
            if (g.merge(a[i - 1][j], a[i][j])) {
                fc.add(g.leader(a[i - 1][j]), 1);
            }
        }
    }
    
    std::cout << ans.val();
    
    return 0;
}
