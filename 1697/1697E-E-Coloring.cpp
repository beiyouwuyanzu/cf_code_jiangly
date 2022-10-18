//url:https://codeforces.com/contest/1697/problem/E
//time:2022-06-12 18:15:26
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
    
    int n;
    std::cin >> n;
    
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    
    std::vector<int> min(n);
    for (int i = 0; i < n; i++) {
        min[i] = 1E9;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                min[i] = std::min(min[i], std::abs(x[i] - x[j]) + std::abs(y[i] - y[j]));
            }
        }
    }
    
    std::vector<std::vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = { i };
        for (int j = 0; j < n; j++) {
            if (min[i] == std::abs(x[i] - x[j]) + std::abs(y[i] - y[j])) {
                a[i].push_back(j);
            }
        }
        std::sort(a[i].begin(), a[i].end());
    }
    
    std::sort(a.begin(), a.end());
    
    std::vector<Z> dp(n + 1);
    dp[0] = 1;
    
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && a[i] == a[j]) {
            j++;
        }
        std::vector<Z> g(n + 1);
        if (j - i == int(a[i].size())) {
            for (int k = 0; k <= i; k++) {
                g[k + 1] += dp[k] * (n - k);
            }
        }
        for (int l = 0; l < j - i; l++) {
            for (int k = i + l + 1; k >= 0; k--) {
                dp[k] = (k > 0 ? dp[k - 1] * (n - k + 1) : Z(0));
            }
        }
        for (int k = 0; k <= j; k++) {
            dp[k] += g[k];
        }
        i = j;
    }
    
    Z ans = std::accumulate(dp.begin(), dp.end(), Z(0));
    
    std::cout << ans << "\n";
    
    return 0;
}

