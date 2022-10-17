//url:https://codeforces.com/contest/1729/problem/G
//time:2022-09-12 18:04:03
//name:G-CutSubstrings

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
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};

void solve() {
    std::string s, t;
    std::cin >> s >> t;
    
    int n = s.length();
    int m = t.length();
    
    std::vector<bool> occur(n);
    int last = -1;
    for (int i = 0; i + m <= n; i++) {
        if (s.substr(i, m) == t) {
            occur[i] = true;
            last = i;
        }
    }
    
    std::vector<std::pair<int, Z>> dp(n + 1, {n + 1, 0});
    dp[0] = {0, 1};
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j <= n; j++) {
            if (j - i >= m && occur[j - m]) {
                break;
            }
            if (occur[j]) {
                if (dp[i].first + 1 < dp[j + m].first) {
                    dp[j + m] = {dp[i].first + 1, dp[i].second};
                } else if (dp[i].first + 1 == dp[j + m].first) {
                    dp[j + m] = {dp[j + m].first, dp[i].second + dp[j + m].second};
                }
            }
        }
    }
    
    std::pair<int, Z> ans{n + 1, 0};
    for (int i = last + 1; i <= n; i++) {
        if (dp[i].first < ans.first) {
            ans = {dp[i].first, dp[i].second};
        } else if (dp[i].first == ans.first) {
            ans = {ans.first, dp[i].second + ans.second};
        }
    }
    std::cout << ans.first << " " << ans.second << "\n";
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
