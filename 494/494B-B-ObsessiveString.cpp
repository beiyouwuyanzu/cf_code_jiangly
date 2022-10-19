// url:https://codeforces.com/contest/494/problem/B
// time:2021-06-21 14:22:00
// name:B-ObsessiveString

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
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s, t;
    std::cin >> s >> t;
    int n = s.size(), m = t.size();
    std::vector<int> nxt(m + 1);
    for (int i = 1, j = 0; i < m; i++) {
        while (j && t[i] != t[j]) {
            j = nxt[j];
        }
        if (t[i] == t[j]) {
            j++;
        }
        nxt[i + 1] = j;
    }
    std::vector<int> occur;
    for (int i = 0, j = 0; i < n; i++) {
        while (j && s[i] != t[j]) {
            j = nxt[j];
        }
        if (s[i] == t[j]) {
            j++;
        }
        if (j == m) {
            occur.push_back(i - m + 1);
            j = nxt[j];
        }
    }
    std::vector<Z> dp(n + 1), sum(n + 1);
    dp[0] = sum[0] = 1;
    for (int i = 1, j = -1; i <= n; i++) {
        while (j + 1 < int(occur.size()) && occur[j + 1] + m <= i) {
            j++;
        }
        dp[i] = dp[i - 1];
        if (j >= 0) {
            dp[i] += sum[occur[j]];
        }
        sum[i] = sum[i - 1] + dp[i];
    }
    Z ans = dp[n] - 1;
    std::cout << ans.val() << "\n";
    return 0;
}
