// url:https://codeforces.com/contest/1620/problem/G
// time:2021-12-18 18:48:32
// name:G-SubsequencesGalore

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
    
    int n;
    std::cin >> n;
    
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    
    std::vector cnt(n, std::vector<int>(26));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            cnt[i][j] = std::count(s[i].begin(), s[i].end(), 'a' + j);
        }
    }
    
    std::vector<int> min(26, 1E9);
    std::vector<Z> f(1 << n);
    std::function<void(int, int)> dfs = [&](int x, int s) {
        if (x == n) {
            Z v = 1;
            for (int i = 0; i < 26; i++) {
                v *= min[i] + 1;
            }
            f[s] = v;
            return;
        }
        dfs(x + 1, s);
        auto tmp = min;
        for (int i = 0; i < 26; i++) {
            min[i] = std::min(min[i], cnt[x][i]);
        }
        dfs(x + 1, s | 1 << x);
        min = std::move(tmp);
    };
    dfs(0, 0);
    
    for (int i = 1; i < (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j += 2 * i) {
            for (int k = 0; k < i; k++) {
                f[j + k] -= f[i + j + k];
            }
        }
    }
    f[0] = 0;
    for (int i = 1; i < (1 << n); i *= 2) {
        for (int j = 0; j < (1 << n); j += 2 * i) {
            for (int k = 0; k < i; k++) {
                f[i + j + k] += f[j + k];
            }
        }
    }
    
    i64 ans = 0;
    for (int s = 0; s < (1 << n); s++) {
        i64 v = (f[(1 << n) - 1] - f[(1 << n) - 1 - s]).val();
        int k = 0, c = 0;
        for (int i = 0; i < n; i++) {
            if (s >> i & 1) {
                c += i + 1;
                k++;
            }
        }
        v *= c * k;
        ans ^= v;
    }
    
    std::cout << ans << "\n";
    
    return 0;
}

