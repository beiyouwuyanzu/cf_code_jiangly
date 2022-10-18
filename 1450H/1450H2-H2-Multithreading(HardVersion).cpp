//url:https://codeforces.com/contest/1450/problem/H2
//time:2021-12-24 14:57:58
//name:H2-Multithreading(HardVersion)

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::string s;
    std::cin >> s;
    
    int x = 0, m = 0, c = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'b') {
            c ^= 1;
        }
        if (s[i] == '?') {
            m++;
            if (i % 2 == 1) {
                c ^= 1;
            }
        } else if ((s[i] == 'b') == (i % 2 == 0)) {
            x++;
        } else {
            x--;
        }
    }
    
    std::vector<Z> fac(n + 1), invfac(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
    }
    invfac[n] = fac[n].inv();
    for (int i = n; i > 0; i--) {
        invfac[i - 1] = invfac[i] * i;
    }
    
    auto binom = [&](int n, int m) -> Z {
        if (m < 0 || n < m) {
            return 0;
        }
        return fac[n] * invfac[m] * invfac[n - m];
    };
    
    std::vector<Z> invp(n + 3);
    invp[0] = 1;
    for (int i = 1; i <= n + 2; i++) {
        invp[i] = invp[i - 1] * ((P + 1) / 2);
    }
    
    Z sum[8];
    
    int u[4];
    u[0] = std::max(-1, std::min((m + x) >> 1, m));
    u[1] = std::max(-1, std::min((m + x - 2) >> 1, m - 1));
    u[2] = std::max(-1, std::min((m - x) >> 1, m));
    u[3] = std::max(-1, std::min((m - x - 2) >> 1, m - 1));
    
    for (int t = 0; t < 4; t++) {
        for (int i = 0; i <= u[t]; i++) {
            sum[t] += binom(m - (t & 1), i);
        }
    }
    
    // std::cerr << c << " " << x << " " << m << "\n";
    
    // Z tmp = 0;
    // for (int i = 0; i <= m; i++) {
    //     tmp += binom(m, i) * std::abs(x + 2 * i - m) * (i & 1 ? -1 : 1);
    // }
    // std::cout << tmp.val() << "\n";
    
    // std::cerr << u[0] << " " << u[1] << " " << u[2] << " " << u[3] << "\n";
    
    auto answer = [&]() {
        for (int i = 0; i < 4; i++) {
            sum[4 + i] = (m - 1 - (i & 1) >= 0 ? binom(m - 1 - (i & 1), u[i]) : u[i] + 1) * (u[i] & 1 ? -1 : 1);
        }
        
        Z res[2];
        for (int v = 0; v < 2; v++) {
            res[v] += sum[4 * v + 0] * (x + m) * (v & m & 1 ? -1 : 1);
            res[v] -= sum[4 * v + 1] * 2 * m * (v & ~m & 1 ? -1 : 1);
            res[v] += sum[4 * v + 2] * (m - x);
            res[v] -= sum[4 * v + 3] * 2 * m * (v & 1 ? -1 : 1);
        }
        Z ans;
        if (c == 0) {
            ans = res[0] + res[1];
        } else {
            ans = res[0] - res[1];
        }
        ans *= invp[m + 2];
        std::cout << ans.val() << "\n";
    };
    
    answer();
    
    while (q--) {
        int j;
        std::cin >> j;
        char ch;
        std::cin >> ch;
        j--;
        
        int nx = x, nm = m, nc = c;
        if (s[j] == 'b') {
            nc ^= 1;
        }
        if (s[j] == '?') {
            nm--;
            if (j % 2 == 1) {
                nc ^= 1;
            }
        } else if ((s[j] == 'b') == (j % 2 == 0)) {
            nx--;
        } else {
            nx++;
        }
        s[j] = ch;
        if (s[j] == 'b') {
            nc ^= 1;
        }
        if (s[j] == '?') {
            nm++;
            if (j % 2 == 1) {
                nc ^= 1;
            }
        } else if ((s[j] == 'b') == (j % 2 == 0)) {
            nx++;
        } else {
            nx--;
        }
        
        int nu[4];
        nu[0] = std::max(-1, std::min((nm + nx) >> 1, nm));
        nu[1] = std::max(-1, std::min((nm + nx - 2) >> 1, nm - 1));
        nu[2] = std::max(-1, std::min((nm - nx) >> 1, nm));
        nu[3] = std::max(-1, std::min((nm - nx - 2) >> 1, nm - 1));
        
        for (int t = 0; t < 4; t++) {
            int tu = u[t];
            int ntu = nu[t];
            int tm = m - (t & 1);
            int ntm = nm - (t & 1);
            while (tu < ntu) {
                tu++;
                sum[t] += binom(tm, tu);
            }
            while (tu > ntu) {
                sum[t] -= binom(tm, tu);
                tu--;
            }
            while (tm < ntm) {
                sum[t] = 2 * sum[t] - binom(tm, tu);
                tm++;
            }
            while (tm > ntm) {
                tm--;
                sum[t] = (sum[t] + binom(tm, tu)) * ((P + 1) / 2);
            }
        }
        
        x = nx;
        m = nm;
        c = nc;
        for (int i = 0; i < 4; i++) {
            u[i] = nu[i];
        }
        
        answer();
    }
    
    return 0;
}

