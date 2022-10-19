// url:https://codeforces.com/contest/1670/problem/C
// time:2022-05-06 18:43:05
// name:C-WhereisthePizza?

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
};

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n), d(n), p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
        p[a[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        b[i]--;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
        d[i]--;
    }
    
    std::vector<bool> vis(n);
    Z ans = 1;
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        int len = 0;
        bool used = false;
        for (int j = i; !vis[j]; j = b[p[j]]) {
            vis[j] = true;
            if (d[p[j]] != -1) {
                used = true;
            }
            len++;
        }
        if (len > 1 && !used) {
            ans *= 2;
        }
    }
    
    std::cout << ans.val() << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
