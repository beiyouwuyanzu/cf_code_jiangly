// url:https://codeforces.com/contest/1542/problem/D
// time:2021-07-03 16:30:33
// name:D-PriorityQueue

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
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::string op;
        std::cin >> op;
        if (op == "+") {
            std::cin >> a[i];
        }
    }
    Z ans;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            continue;
        }
        std::vector<Z> dp(n + 1);
        dp[0] = 1;
        Z mul = 1;
        for (int j = 0; j < n; j++) {
            if (j < i ? a[j] > a[i] : a[j] >= a[i]) {
                if (j != i) {
                    mul *= 2;
                }
                continue;
            }
            if (a[j] == 0) {
                for (int k = 0; k <= j; k++) {
                    if (j < i || k > 0) {
                        dp[std::max(0, k - 1)] += dp[k];
                    }
                }
            } else {
                for (int k = j; k >= 0; k--) {
                    dp[k + 1] += dp[k];
                }
            }
        }
        ans += mul * std::accumulate(dp.begin(), dp.end(), Z(0)) * a[i];
    }
    std::cout << ans.val() << "\n";
    return 0;
}
