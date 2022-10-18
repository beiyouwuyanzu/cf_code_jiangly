//url:https://codeforces.com/contest/1086/problem/F
//time:2021-07-15 20:26:39
//name:F-ForestFires

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
    
    int n, t;
    std::cin >> n >> t;
    
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    
    auto calc = [&](int t) {
        std::vector<int> v;
        v.reserve(2 * n);
        
        std::vector<std::tuple<int, int, int, int>> events;
        events.reserve(2 * n);
        for (int i = 0; i < n; i++) {
            v.push_back(y[i] - t);
            v.push_back(y[i] + 1 + t);
            events.emplace_back(x[i] - t, y[i] - t, y[i] + t + 1, 1);
            events.emplace_back(x[i] + t + 1, y[i] - t, y[i] + t + 1, -1);
        }
        
        Z ans;
        
        std::sort(v.begin(), v.end());
        std::vector<int> a(2 * n - 1);
        std::sort(events.begin(), events.end());
        
        int lst = 0;
        Z sum;
        for (auto [x, l, r, w] : events) {
            l = std::lower_bound(v.begin(), v.end(), l) - v.begin();
            r = std::lower_bound(v.begin(), v.end(), r) - v.begin();
            
            ans += sum * (x - lst);
            lst = x;
            
            for (int i = l; i < r; i++) {
                if (a[i] > 0) {
                    sum -= v[i + 1] - v[i];
                }
                a[i] += w;
                if (a[i] > 0) {
                    sum += v[i + 1] - v[i];
                }
            }
        }
        
        return ans;
    };
    
    Z ans = calc(t) * t;
    
    std::vector<int> a{0};
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            a.push_back(std::max(std::abs(x[i] - x[j]), std::abs(y[i] - y[j])) / 2);
        }
    }
    
    std::sort(a.begin(), a.end());
    while (!a.empty() && a.back() >= t) {
        a.pop_back();
    }
    a.push_back(t);
    
    for (int i = 0; i < int(a.size()) - 1; i++) {
        std::vector<Z> f(4);
        for (int j = 0; j < 3; j++) {
            f[j + 1] = f[j] + calc(a[i] + j);
        }
        
        Z res = 0, x = a[i + 1] - a[i];
        for (int j = 0; j <= 3; j++) {
            Z v = f[j];
            for (int k = 0; k <= 3; k++) {
                if (j == k) {
                    continue;
                }
                
                v *= (x - k);
                v /= (j - k);
            }
            
            res += v;
        }
        
        ans -= res;
    }
    
    std::cout << ans.val() << "\n";
    
    return 0;
}
