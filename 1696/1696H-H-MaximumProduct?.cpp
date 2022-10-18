//url:https://codeforces.com/contest/1696/problem/H
//time:2022-06-25 19:40:34
//name:H-MaximumProduct?

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a.begin(), a.end(), [&](int x, int y) {
        return std::abs(x) < std::abs(y);
    });
    
    Z ans = 0;
    
    std::vector<Z> p2(n + 1);
    p2[0] = 1;
    for (int i = 1; i <= n; i++) {
        p2[i] = p2[i - 1] * 2;
    }
    
    std::vector pre(3, std::vector<int>(n + 1));
    for (int x = 0; x < 3; x++) {
        for (int i = 0; i < n; i++) {
            pre[x][i + 1] = pre[x][i] + (x == 0 ? a[i] > 0 : x == 1 ? a[i] < 0 : a[i] == 0);
        }
    }
    
    if (k % 2 == 1) {
        std::vector<Z> dp(k);
        dp[0] = 1;
        for (int i = 0; i < n; i++) {
            if (a[i] >= 0) {
                continue;
            }
            ans += dp[k - 1] * a[i] * (p2[pre[1][n] - pre[1][i + 1]] - 1);
            for (int j = k - 1; j > 0; j--) {
                dp[j] += dp[j - 1] * a[i];
            }
        }
        dp.assign(k, 0);
        dp[0] = 1;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] >= 0) {
                continue;
            }
            for (int j = i - 1; j >= 0; j--) {
                if (a[j] > 0) {
                    ans += dp[k - 1] * a[j] * p2[pre[0][j] + pre[1][i] + pre[2][n]];
                }
            }
            for (int j = k - 1; j > 0; j--) {
                dp[j] += dp[j - 1] * a[i];
            }
        }
    }
    
    std::vector dp(2, std::vector<Z>(k));
    dp[0][0] = 1;
    
    for (int j = n - 1; j >= 0; j--) {
        if (a[j] == 0) {
            break;
        }
        ans += (dp[0][k - 1] + dp[1][k - 1]) * a[j];
        ans += dp[a[j] < 0][k - 1] * a[j] * (p2[j] - 1);
        
        std::vector g(2, std::vector<Z>(k));
        for (int i = k - 1; i > 0; i--) {
            g[0][i] = dp[a[j] < 0][i - 1];
            g[1][i] = dp[a[j] > 0][i - 1];
        }
        for (int i = j - 1; i >= 0; i--) {
            if (a[i] == 0) {
                break;
            }
            if ((a[i] > 0) == (a[j] > 0)) {
                continue;
            }
            Z res = g[a[i] > 0][k - 1];
            
            for (int x = i - 1, y = i - 1; x >= 0; x--) {
                if (a[x] == 0 || (a[x] > 0) != (a[i] > 0)) {
                    continue;
                }
                while (y >= 0 && 1LL * std::abs(a[y]) * std::abs(a[j]) > 1LL * a[x] * a[i]) {
                    y--;
                }
                ans += res * a[i] * a[x] * p2[pre[a[x] < 0][x] + pre[a[x] > 0][y + 1] + pre[2][n]];
            }
            
            for (int x = i - 1, y = i - 1; x >= 0; x--) {
                if (a[x] == 0 || (a[x] > 0) != (a[j] > 0)) {
                    continue;
                }
                while (y >= 0 && 1LL * std::abs(a[y]) * std::abs(a[i]) >= 1LL * a[x] * a[j]) {
                    y--;
                }
                ans += res * a[j] * a[x] * p2[pre[a[x] < 0][x] + pre[a[x] > 0][y + 1] + pre[2][n]];
            }
            
            for (int x = k - 1; x > 0; x--) {
                g[0][x] += g[a[i] < 0][x - 1] * a[i];
                g[1][x] += g[a[i] > 0][x - 1] * a[i];
            }
        }
        for (int i = k - 1; i > 0; i--) {
            dp[0][i] += dp[a[j] < 0][i - 1] * a[j];
            dp[1][i] += dp[a[j] > 0][i - 1] * a[j];
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}

