// url:https://codeforces.com/contest/1635/problem/D
// time:2022-02-20 18:18:26
// name:D-InfiniteSet

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
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, p;
    std::cin >> n >> p;
    
    Z ans = 0;
    
    std::vector<Z> f(p + 1);
    f[0] = 1;
    for (int i = 1; i <= p; i++) {
        f[i] = f[i - 1];
        if (i > 1) {
            f[i] += f[i - 2];
        }
    }
    for (int i = 1; i <= p; i++) {
        f[i] += f[i - 1];
    }
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::set<int> s;
    std::sort(a.begin(), a.end());
    
    for (auto x : a) {
        bool good = true;
        int v = x;
        while (v > 0) {
            if (s.count(v)) {
                good = false;
                break;
            }
            if (v % 2 == 1) {
                v /= 2;
            } else if (v % 4 == 0) {
                v /= 4;
            } else {
                break;
            }
        }
        if (!good) {
            continue;
        }
        s.insert(x);
        
        int b = std::__lg(x) + 1;
        if (b <= p) {
            ans += f[p - b];
        }
    }
    
    std::cout << ans.val() << "\n";
    
    return 0;
}
