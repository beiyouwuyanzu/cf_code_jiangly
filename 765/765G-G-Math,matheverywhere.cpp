//url:https://codeforces.com/contest/765/problem/G
//time:2021-07-12 18:58:43
//name:G-Math,matheverywhere

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

Z f[19 << 22], g[23 << 18];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    
    int m = s.length();
    i64 goal = 0;
    for (int i = 0; i < m; i++) {
        goal += i64(s[i] - '0') << i;
    }
    
    int n;
    std::cin >> n;
    
    Z ans = 1;
    
    std::vector<int> p(n);
    
    for (int i = 0; i < n; i++) {
        int a;
        std::cin >> p[i] >> a;
        
        ans *= power(Z(p[i]), a - 1);
    }
    
    std::sort(p.begin(), p.end());
    
    int k = 0;
    while (k < n && p[k] < 29) {
        k++;
    }
    
    std::vector<std::pair<i64, Z>> states{{(1LL << m) - 1, 1}};
    std::vector<std::pair<i64, Z>> newStates;
    
    if (k == 0) {
        if (p[0] < m) {
            int d = m - p[0];
            f[((m - 2 * d + 1) << (2 * d)) - 1] += 1;
        } else {
            f[m] += 1;
        }
    }
    
    for (int i = 0; i < k; i++) {
        newStates.clear();
        
        for (int j = 0; j < p[i]; j++) {
            i64 t = (1ll << m) - 1;
            for (int x = j; x < m; x += p[i]) {
                t &= ~(1ll << x);
            }
            
            if ((t & goal) != goal) {
                continue;
            }
            
            for (auto [x, y] : states) {
                x &= t;
                if (i < k - 1) {
                    newStates.emplace_back(x & t, y);
                } else if (k == n || p[k] >= m) {
                    f[__builtin_popcountll(x)] += y;
                } else {
                    int d = m - p[k];
                    int c = __builtin_popcountll(x >> d & ((1LL << (p[k] - d)) - 1));
                    x = (x & ((1 << d) - 1)) | (x >> p[k] << d);
                    f[c << (2 * d) | x] += y;
                }
            }
        }
        
        std::sort(newStates.begin(), newStates.end(), [&](const auto &a, const auto &b) { return a.first < b.first; });
        
        int cnt = newStates.size();
        states.clear();
        for (int l = 0, r; l < cnt; l = r) {
            for (r = l; r < cnt && newStates[l].first == newStates[r].first; r++)
                ;
            
            Z sum = 0;
            for (int i = l; i < r; i++) {
                sum += newStates[i].second;
            }
            
            states.emplace_back(newStates[l].first, sum);
        }
    }
    
    while (k < n && p[k] < m) {
        std::memset(g, 0, sizeof(g));
        
        int d = m - p[k];
        for (int mask = 0; mask < ((m - 2 * d + 1) << (2 * d)); mask++) {
            if (f[mask].val() == 0) {
                continue;
            }
            
            int c = mask >> (2 * d);
            int x = mask & ((1 << (2 * d)) - 1);
            
            Z val = f[mask];
            
            for (int i = 0; i < d; i++) {
                if (goal >> i & 1) {
                    continue;
                }
                if (goal >> (i + p[k]) & 1) {
                    continue;
                }
                
                int t = x & ~(1 << i) & ~(1 << (i + d));
                if (k + 1 == n || p[k + 1] >= m) {
                    g[__builtin_popcount(t) + c] += val;
                } else {
                    int d1 = m - p[k + 1];
                    int c1 = c + __builtin_popcount(t >> d1 & ((1 << (2 * (d - d1))) - 1));
                    t = (t & ((1 << d1) - 1)) | (t >> (2 * d - d1) << d1);
                    g[c1 << (2 * d1) | t] += val;
                }
            }
            
            int cnt = __builtin_popcountll(goal >> d & ((1LL << (m - 2 * d)) - 1));
            if (k + 1 == n || p[k + 1] >= m) {
                if (c > cnt) {
                    g[__builtin_popcount(x) + c - 1] += val * (c - cnt);
                }
                g[__builtin_popcount(x) + c] += val * (m - 2 * d - c);
            } else {
                int d1 = m - p[k + 1];
                int c1 = c + __builtin_popcount(x >> d1 & ((1 << (2 * (d - d1))) - 1));
                x = (x & ((1 << d1) - 1)) | (x >> (2 * d - d1) << d1);
                g[c1 << (2 * d1) | x] += val * (m - 2 * d - c);
                if (c > cnt) {
                    g[(c1 - 1) << (2 * d1) | x] += val * (c - cnt);
                }
            }
        }
        
        k++;
        std::memcpy(f, g, sizeof(g));
    }
    
    int cnt = __builtin_popcountll(goal);
    
    for (int i = k; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            f[j] *= (p[i] - j);
            if (j < m) {
                f[j] += f[j + 1] * (j + 1 - cnt);
            }
        }
    }
    
    ans *= f[cnt];
    
    std::cout << ans.val() << "\n";
    
    return 0;
}
