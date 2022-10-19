// url:https://codeforces.com/contest/497/problem/E
// time:2021-06-20 20:12:24
// name:E-SubsequencesReturn

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
constexpr int K = 31;
struct Matrix {
    Z a[K][K];
    Matrix(int x = 0) : a{} {
        for (int i = 0; i < K; i++) {
            a[i][i] = x;
        }
    }
};
Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix res;
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < K; k++) {
                res.a[i][j] += a.a[i][k] * b.a[k][j];
            }
        }
    }
    return res;
}
Matrix shift(const Matrix &a, int d, int k) {
    Matrix res;
    res.a[k][k] = 1;
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            res.a[(i + d) % k][(j + d) % k] = a.a[i][j];
        }
        res.a[k][(i + d) % k] = a.a[k][i];
    }
    return res;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    i64 n;
    int k;
    std::cin >> n >> k;
    Matrix ans(1);
    Matrix g(1);
    for (int i = 0; i <= k; i++) {
        g.a[i][0] = 1;
    }
    std::vector<int> d;
    while (n) {
        d.push_back(n % k);
        n /= k;
    }
    int m = d.size();
    int s = std::accumulate(d.begin(), d.end(), 0);
    for (int i = 0; i < m; i++) {
        s -= d[i];
        for (int j = d[i] - 1; j >= 0; j--) {
            ans = shift(g, j + s, k) * ans;
        }
        Matrix f(1);
        for (int j = 0; j < k; j++) {
            f = f * shift(g, j, k);
        }
        g = f;
    }
    Z sum;
    for (int i = 0; i <= k; i++) {
        sum += ans.a[k][i];
    }
    std::cout << sum.val() << "\n";
    return 0;
}
