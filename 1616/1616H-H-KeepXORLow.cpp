// url:https://codeforces.com/contest/1616/problem/H
// time:2021-12-30 11:24:51
// name:H-KeepXORLow

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
    
    int n, x;
    std::cin >> n >> x;
    
    Z ans = 0;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    
    std::vector<Z> pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = 2 * pw[i - 1];
    }
    
    int k = x == 0 ? 0 : 1 + std::__lg(x);
    
    std::function<Z(int, int, int, int, int)> work = [&](int l1, int r1, int l2, int r2, int k) {
        if (k == 0 || l1 == r1 || l2 == r2) {
            return pw[r1 - l1 + r2 - l2];
        }
        int m1 = std::partition_point(a.begin() + l1, a.begin() + r1, [&](int x) { return ~x >> (k - 1) & 1; }) - a.begin();
        int m2 = std::partition_point(a.begin() + l2, a.begin() + r2, [&](int x) { return ~x >> (k - 1) & 1; }) - a.begin();
        
        if (x >> (k - 1) & 1) {
            return work(l1, m1, m2, r2, k - 1) * work(m1, r1, l2, m2, k - 1);
        } else {
            return work(l1, m1, l2, m2, k - 1) + work(m1, r1, m2, r2, k - 1) - 1
                 + (pw[m1 - l1] - 1) * (pw[r1 - m1] - 1) + (pw[m2 - l2] - 1) * (pw[r2 - m2] - 1);
        }
    };
    
    for (int i = 0, j = 0; i < n; i = j) {
        j = i;
        while (j < n && (a[i] >> k) == (a[j] >> k)) {
            j++;
        }
        if (x == 0) {
            ans += pw[j - i] - 1;
        } else {
            int m = std::partition_point(a.begin() + i, a.begin() + j, [&](int x) { return ~x >> (k - 1) & 1; }) - a.begin();
            ans += work(i, m, m, j, k - 1) - 1;
        }
    }
    
    std::cout << ans.val() << "\n";
    
    return 0;
}

