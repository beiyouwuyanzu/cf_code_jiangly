//url:https://codeforces.com/contest/1574/problem/E
//time:2022-06-12 09:25:25
//name:E-Coloring

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
    
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<Z> p(std::max(n, m) + 1);
    p[0] = 1;
    for (int i = 1; i <= std::max(n, m); i++) {
        p[i] = 2 * p[i - 1];
    }
    
    int badRow = 0, badCol = 0;
    
    int row = 0, col = 0;
    
    int rc[2] = {};
    
    std::vector<std::array<int, 2>> r(n), c(m);
    
    std::map<std::array<int, 2>, int> entry;
    
    auto add = [&](int x, int y, int t) {
        badRow -= (r[x][0] > 0 && r[x][1] > 0);
        row -= (r[x][0] > 0 || r[x][1] > 0);
        r[x][(y & 1) ^ t]++;
        row += (r[x][0] > 0 || r[x][1] > 0);
        badRow += (r[x][0] > 0 && r[x][1] > 0);
        
        badCol -= (c[y][0] > 0 && c[y][1] > 0);
        col -= (c[y][0] > 0 || c[y][1] > 0);
        c[y][(x & 1) ^ t]++;
        col += (c[y][0] > 0 || c[y][1] > 0);
        badCol += (c[y][0] > 0 && c[y][1] > 0);
        
        rc[((x ^ y) & 1) ^ t]++;
    };
    
    auto remove = [&](int x, int y, int t) {
        badRow -= (r[x][0] > 0 && r[x][1] > 0);
        row -= (r[x][0] > 0 || r[x][1] > 0);
        r[x][(y & 1) ^ t]--;
        row += (r[x][0] > 0 || r[x][1] > 0);
        badRow += (r[x][0] > 0 && r[x][1] > 0);
        
        badCol -= (c[y][0] > 0 && c[y][1] > 0);
        col -= (c[y][0] > 0 || c[y][1] > 0);
        c[y][(x & 1) ^ t]--;
        col += (c[y][0] > 0 || c[y][1] > 0);
        badCol += (c[y][0] > 0 && c[y][1] > 0);
        
        rc[((x ^ y) & 1) ^ t]--;
    };
    
    for (int i = 0; i < k; i++) {
        int x, y, t;
        std::cin >> x >> y >> t;
        x--;
        y--;
        
        if (entry.contains({ x, y })) {
            remove(x, y, entry[{ x, y }]);
            entry.erase({ x, y });
        }
        if (t != -1) {
            add(x, y, t);
            entry[{ x, y }] = t;
        }
        
        Z ans = 0;
        if (badRow == 0) {
            ans += p[n - row];
        }
        if (badCol == 0) {
            ans += p[m - col];
        }
        if (rc[0] == 0) {
            ans -= 1;
        }
        if (rc[1] == 0) {
            ans -= 1;
        }
        
        std::cout << ans << "\n";
    }
    
    return 0;
}

