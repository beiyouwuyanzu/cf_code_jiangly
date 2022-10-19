// url:https://codeforces.com/contest/715/problem/E
// time:2021-07-07 14:26:25
// name:E-CompletethePermutations

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
    
    int n;
    std::cin >> n;
    
    std::vector<int> p(n), q(n);
    std::vector<bool> asp(n), asq(n);
    
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
        if (p[i] >= 0) {
            asp[p[i]] = true;
        }
    }
    for (int i = 0; i < n; i++) {
        std::cin >> q[i];
        q[i]--;
        if (q[i] >= 0) {
            asq[q[i]] = true;
        }
    }
    
    std::vector<Z> fac(n + 1);
    std::vector C(n + 1, std::vector<Z>(n + 1));
    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i;
    }
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
    
    std::vector<int> r(n, -1), ir(n, -1);
    for (int i = 0; i < n; i++) {
        if (p[i] >= 0 && q[i] >= 0) {
            r[p[i]] = q[i];
            ir[q[i]] = p[i];
        }
    }
    
    std::vector<Z> ans(n);
    
    int cyc = 0;
    int cnt[2][2] = {};
    std::vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        if (ir[i] >= 0) {
            continue;
        }
        int j = i, k = -1;
        while (j >= 0) {
            vis[j] = true;
            k = j;
            j = r[j];
        }
        cnt[asq[i]][asp[k]]++;
    }
    
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        int j = i;
        while (!vis[j]) {
            vis[j] = true;
            j = r[j];
        }
        cyc++;
    }
    
    std::vector coef(n + 1, std::vector<Z>(n + 1));
    
    for (int x = 0; x <= cnt[0][1] && x <= cnt[1][0]; x++) {
        for (int y = 0; y <= cnt[1][1]; y++) {
            int u = cnt[0][1] - x;
            int v = cnt[1][0] - x;
            int all = x + u + v;
            coef[all + cnt[0][0]][cnt[1][1] - y] += C[cnt[0][1]][x] * C[cnt[1][0]][x] * fac[x] * fac[y] * C[cnt[1][1]][y] * (all == 0 ? y == 0 : C[y + all - 1][y]) * ((x + y) % 2 == 0 ? 1 : -1);
        }
    }
    
    std::vector s(n + 1, std::vector<Z>(n + 1));
    for (int i = 0; i <= n; i++) {
        s[i][0] = (i == 0);
        for (int j = 1; j <= i; j++) {
            s[i][j] = s[i - 1][j - 1] + s[i - 1][j] * (i - 1);
        }
    }
    
    std::vector coef2(n + 1, std::vector<Z>(n + 1));
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (coef[i][j].val() == 0) {
                continue;
            }
            for (int b = 0; b <= i; b++) {
                for (int c = j; c <= i - b; c++) {
                    coef2[b][j] += s[i - c][b] * (j == 0 ? c == 0 : C[c - 1][j - 1]) * C[i][c] * fac[c] * coef[i][j];
                }
            }
        }
    }
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (coef2[i][j].val() == 0) {
                continue;
            }
            for (int a = (j > 0); a <= j; a++) {
                ans[n - cyc - i - a] += s[j][a] * coef2[i][j];
            }
        }
    }
    
    int free = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] < 0 && q[i] < 0) {
            free++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        ans[i] *= fac[free];
        std::cout << ans[i].val() << " \n"[i == n - 1];
    }
    
    return 0;
}
