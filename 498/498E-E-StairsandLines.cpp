// url:https://codeforces.com/contest/498/problem/E
// time:2021-06-21 22:14:48
// name:E-StairsandLines

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
using Matrix = std::vector<std::vector<Z>>;
int Size = 0;
Matrix operator*(const Matrix &a, const Matrix &b) {
    Matrix c(Size, std::vector<Z>(Size));
    for (int i = 0; i < Size; i++) {
        for (int j = 0; j < Size; j++) {
            for (int k = 0; k < Size; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}
std::vector<Z> operator*(const std::vector<Z> &a, const Matrix &b) {
    std::vector<Z> c(Size);
    for (int j = 0; j < Size; j++) {
        for (int k = 0; k < Size; k++) {
            c[j] += a[k] * b[k][j];
        }
    }
    return c;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<Z> dp{1};
    for (int h = 1; h <= 7; h++) {
        int w;
        std::cin >> w;
        dp.insert(dp.begin(), 1 << (h - 1), 0);
        Size = 1 << h;
        Matrix g(Size, std::vector<Z>(Size));
        for (int s = 0; s < Size; s++) {
            for (int t = 0; t < Size; t++) {
                Z f[2];
                f[1] = 1;
                for (int i = 0; i < h; i++) {
                    Z f1[2];
                    f1[0] = f[0] + f[1];
                    f1[1] = f[0] + !((s & t) >> i & 1) * f[1];
                    f[0] = f1[0];
                    f[1] = f1[1];
                }
                g[s][t] = f[1];
            }
        }
        for (; w; w /= 2, g = g * g) {
            if (w & 1) {
                dp = dp * g;
            }
        }
    }
    std::cout << dp.back().val() << "\n";
    return 0;
}
