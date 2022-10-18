//url:https://codeforces.com/contest/1623/problem/D
//time:2021-12-28 17:27:45
//name:D-RobotCleanerRevisit

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

void solve() {
    int n, m, rb, cb, rd, cd, pp;
    std::cin >> n >> m >> rb >> cb >> rd >> cd >> pp;
    rb--;
    cb--;
    rd--;
    cd--;
    
    const Z p = Z(pp) / 100;
    
    int x = rb, y = cb, dx = 1, dy = 1;
    int nx = x + dx;
    int ny = y + dy;
    if (nx < 0 || nx >= n) {
        dx = -dx;
    }
    if (ny < 0 || ny >= m) {
        dy = -dy;
    }
    const int idx = dx, idy = dy;
    
    int len = 0;
    Z pr = 1, ans = 0; 
    do {
        if (x == rd || y == cd) {
            ans += pr * p * len;
            pr *= (1 - p);
        }
        len++;
        
        x += dx;
        y += dy;
        
        int nx = x + dx;
        int ny = y + dy;
        if (nx < 0 || nx >= n) {
            dx = -dx;
        }
        if (ny < 0 || ny >= m) {
            dy = -dy;
        }
    } while (std::tuple(x, y, dx, dy) != std::tuple(rb, cb, idx, idy));
    
    ans = (ans + len * pr) / (1 - pr);
    
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

