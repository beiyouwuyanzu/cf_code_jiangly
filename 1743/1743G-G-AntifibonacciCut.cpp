// url:https://codeforces.com/contest/1743/problem/G
// time:2022-10-17 18:30:08
// name:G-AntifibonacciCut

#include <bits/stdc++.h>

using i64 = long long;

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

std::vector<int> fib{1, 2};

int get(int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 0;
    }
    auto it = std::prev(std::upper_bound(fib.begin(), fib.end(), n));
    return get(n - *it);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    for (int i = 0; i < 30; i++) {
        fib.push_back(fib[fib.size() - 2] + fib.back());
    }
    
    int n;
    std::cin >> n;
    
    Z dp = 1, sum = 1;
    std::vector<std::pair<int, Z>> suf;
    
    auto add = [&](int x) {
        Z ndp = sum - dp;
        std::vector<std::pair<int, Z>> nsuf;
        
        if (x) {
            nsuf.push_back({1, dp});
        }
        for (auto [l, v] : suf) {
            if (x == get(l)) {
                nsuf.emplace_back(l + 1, v);
                if (std::binary_search(fib.begin(), fib.end(), l + 1)) {
                    ndp -= v;
                }
            }
        }
        std::swap(suf, nsuf);
        dp = ndp;
        
        sum += ndp;
    };
    
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        
        for (auto c : s) {
            add(c - '0');
        }
        std::cout << dp << "\n";
    }
    
    
    return 0;
}
