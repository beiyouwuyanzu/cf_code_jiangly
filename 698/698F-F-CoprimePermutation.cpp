//url:https://codeforces.com/contest/698/problem/F
//time:2021-07-12 21:12:26
//name:F-CoprimePermutation

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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> p[i];
    }
    
    std::vector<bool> isprime(n + 1);
    std::fill(isprime.begin() + 2, isprime.end(), true);
    std::vector<int> primes, simp(n + 1), type(n + 1), gp(n + 1);
    simp[1] = 1;
    type[1] = 1;
    gp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        if (isprime[i]) {
            primes.push_back(i);
            simp[i] = i;
            type[i] = n / i;
            gp[i] = i;
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            
            isprime[i * p] = false;
            gp[i * p] = gp[i];
            if (i % p == 0) {
                simp[i * p] = simp[i];
                break;
            } else {
                simp[i * p] = simp[i] * p;
            }
        }
    }
    
    std::vector<int> cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cnt[simp[i]]++;
    }
    
    Z ans = 1;
    
    std::vector<int> t(n + 1), rt(n + 1);
    
    for (int i = 1; i <= n; i++) {
        if (p[i] == 0) {
            continue;
        }
        
        int a = simp[i], b = simp[p[i]];
        if (type[gp[a]] != type[gp[b]]) {
            std::cout << "0\n";
            return 0;
        }
        
        if (t[gp[a]] > 0 && t[gp[a]] != gp[b]) {
            std::cout << "0\n";
            return 0;
        }
        
        if (rt[gp[b]] > 0 && rt[gp[b]] != gp[a]) {
            std::cout << "0\n";
            return 0;
        }
        
        if (gp[a] / a != gp[b] / b) {
            std::cout << "0\n";
            return 0;
        }
        
        t[gp[a]] = gp[b];
        rt[gp[b]] = gp[a];
        
        cnt[a]--;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= cnt[i]; j++) {
            ans *= j;
        }
    }
    
    cnt.assign(n + 1, 0);
    
    for (auto p : primes) {
        if (t[p] == 0) {
            cnt[type[p]]++;
        }
    }
    if (t[1] == 0) {
        cnt[1]++;
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= cnt[i]; j++) {
            ans *= j;
        }
    }
    
    std::cout << ans.val() << "\n";
    
    return 0;
}
