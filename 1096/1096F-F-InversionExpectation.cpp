//url:https://codeforces.com/contest/1096/problem/F
//time:2021-07-15 21:11:47
//name:F-InversionExpectation

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


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> p(n);
    std::vector<int> sum(n + 1, 1);
    sum[0] = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        if (p[i] > 0) {
            sum[p[i]] = 0;
            p[i]--;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        sum[i] += sum[i - 1];
    }
    
    std::vector<int> blank(n + 1);
    for (int i = 0; i < n; i++) {
        blank[i + 1] = blank[i] + (p[i] < 0);
    }
    
    int unknown = std::count(p.begin(), p.end(), -1);
    Z inv = unknown > 0 ? Z(unknown).inv() : 0;
    
    Z ans;
    
    Fenwick<int> fen(n);
    for (int i = n - 1; i >= 0; i--) {
        if (p[i] < 0) {
            continue;
        }
        
        ans += Z(blank[i]) * (sum[n] - sum[p[i] + 1]) * inv;
        ans += Z(blank[n] - blank[i + 1]) * sum[p[i]] * inv;
        ans += fen.sum(p[i]);
        fen.add(p[i], 1);
    }
    
    ans += Z(unknown) * (unknown - 1) / 4;
    
    std::cout << ans.val() << "\n";
    
    return 0;
}
