//url:https://codeforces.com/contest/1574/problem/F
//time:2022-06-12 10:11:44
//name:F-Occurrences

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
    
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<int> belong(k, n);
    
    std::vector<std::vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        int c;
        std::cin >> c;
        a[i].resize(c);
        
        for (int j = 0; j < c; j++) {
            std::cin >> a[i][j];
            a[i][j]--;
        }
    }
    
    std::sort(a.begin(), a.end(), [&](auto x, auto y) {
        return x.size() < y.size();
    });
    
    for (int i = 0; i < n; i++) {
        bool nice = true;
        std::set<int> s(a[i].begin(), a[i].end());
        if (a[i].size() != s.size()) {
            nice = false;
        } else if (std::find_if(a[i].begin(), a[i].end(), [&](int x) {
                    return belong[x] == -1;
                }) != a[i].end()) {
            nice = false;
        } else {
            int len = a[i].size();
            for (int j = 0; j < len; ) {
                int v = a[i][j];
                v = belong[v];
                
                if (v == n) {
                    j++;
                    continue;
                }
                
                int lenv = a[v].size();
                int p = std::find(a[v].begin(), a[v].end(), a[i][j]) - a[v].begin();
                if (j > 0 && p > 0) {
                    nice = false;
                    break;
                }
                int l = std::min(lenv - p, len - j);
                if (!std::equal(a[v].begin() + p, a[v].begin() + p + l, a[i].begin() + j, a[i].begin() + j + l)) {
                    nice = false;
                    break;
                }
                for (int x = 0; x < lenv; x++) {
                    if ((x < p || x >= p + l) && s.contains(a[v][x])) {
                        nice = false;
                    }
                }
                if (!nice) {
                    break;
                }
                
                if (p > 0) {
                    a[i].insert(a[i].begin(), a[v].begin(), a[v].begin() + p);
                    j += p;
                }
                if (p + l < lenv) {
                    a[i].insert(a[i].end(), a[v].begin() + p + l, a[v].end());
                    j += lenv - p - l;
                }
                len = a[i].size();
                j += l;
            }
        }
        if (!nice) {
            for (auto c : a[i]) {
                if (belong[c] == n) {
                    belong[c] = -1;
                } else if (belong[c] != -1) {
                    for (auto x : a[belong[c]]) {
                        belong[x] = -1;
                    }
                }
            }
        } else {
            for (auto c : a[i]) {
                belong[c] = i;
            }
        }
    }
    
    std::vector<Z> dp(m + 1), cnt(m + 1);
    dp[0] = 1;
    
    for (int i = 0; i < k; i++) {
        if (belong[i] == n) {
            cnt[1] += 1;
        } else if (belong[i] != -1 && i == a[belong[i]][0]) {
            cnt[a[belong[i]].size()] += 1;
        }
    }
    
    std::vector<std::pair<int, Z>> f;
    for (int i = 1; i <= m; i++) {
        if (cnt[i].val() != 0) {
            f.emplace_back(i, cnt[i]);
        }
    }
    
    for (int i = 1; i <= m; i++) {
        for (auto [j, x] : f) {
            if (j <= i) {
                dp[i] += dp[i - j] * x;
            }
        }
    }
    
    std::cout << dp[m] << "\n";
    
    return 0;
}

