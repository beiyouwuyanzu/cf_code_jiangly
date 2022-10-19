// url:https://codeforces.com/contest/1679/problem/E
// time:2022-05-16 15:43:01
// name:E-TypicalPartyinDorm

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
    
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    int q;
    std::cin >> q;
    
    std::vector<std::string> qs(q);
    for (int i = 0; i < q; i++) {
        std::cin >> qs[i];
    }
    
    std::vector<Z> ans(q);
    
    for (int len = 1; len <= 17; len++) {
        std::vector<Z> a(1 << 17);
        std::vector<Z> pw(n + 1);
        pw[0] = 1;
        for (int i = 1; i <= n; i++) {
            pw[i] = pw[i - 1] * len;
        }
        int tot = std::count(s.begin(), s.end(), '?');
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            int mask = 0;
            a[mask] += pw[tot];
            for (int j = 1; i - j >= 0 && i + j < n; j++) {
                int l = i - j;
                int r = i + j;
                if (s[l] == '?' && s[r] == '?') {
                    cnt++;
                } else if (s[l] == '?') {
                    cnt++;
                    mask |= 1 << (s[r] - 'a');
                } else if (s[r] == '?') {
                    cnt++;
                    mask |= 1 << (s[l] - 'a');
                } else if (s[l] != s[r]) {
                    break;
                }
                a[mask] += pw[tot - cnt];
            }
        }
        for (int i = 1; i < n; i++) {
            int cnt = 0;
            int mask = 0;
            for (int j = 0; i - j - 1 >= 0 && i + j < n; j++) {
                int l = i - j - 1;
                int r = i + j;
                if (s[l] == '?' && s[r] == '?') {
                    cnt++;
                } else if (s[l] == '?') {
                    cnt++;
                    mask |= 1 << (s[r] - 'a');
                } else if (s[r] == '?') {
                    cnt++;
                    mask |= 1 << (s[l] - 'a');
                } else if (s[l] != s[r]) {
                    break;
                }
                a[mask] += pw[tot - cnt];
            }
        }
        
        for (int i = 1; i < (1 << 17); i *= 2) {
            for (int j = 0; j < (1 << 17); j += 2 * i) {
                for (int k = 0; k < i; k++) {
                    a[i + j + k] += a[j + k];
                }
            }
        }
        
        for (int i = 0; i < q; i++) {
            if (int(qs[i].length()) == len) {
                int mask = 0;
                for (auto c : qs[i]) {
                    mask |= 1 << (c - 'a');
                }
                ans[i] = a[mask];
            }
        }
    }
    
    for (int i = 0; i < q; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
