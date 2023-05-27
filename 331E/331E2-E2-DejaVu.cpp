// url:https://codeforces.com/contest/331/problem/E2
// time:2023-04-27 07:13:41
// name:E2-DejaVu

#include <bits/stdc++.h>

using i64 = long long;
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<i64 P>
struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    
    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
i64 MLong<0LL>::Mod = 1;

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 1;

template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = 1000000007;
using Z = MInt<P>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector e(n, std::vector(n, false));
    std::vector v(n, std::vector(n, std::vector<int>()));
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        e[x][y] = true;
        int k;
        std::cin >> k;
        v[x][y].resize(k);
        for (int j = 0; j < k; j++) {
            std::cin >> v[x][y][j];
            v[x][y][j]--;
        }
    }
    
    std::vector<std::tuple<int, int, int>> f[2][2];
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (e[x][y]) {
                for (int i = 0; i <= v[x][y].size(); i++) {
                    if ((!i || v[x][y][i-1] == x) && (i == v[x][y].size() || v[x][y][i] == y)) {
                        std::vector<int> l, r;
                        l.assign(v[x][y].rend() - i, v[x][y].rend());
                        if (!l.empty()) {
                            bool ok = true;
                            for (int j = 0; j+1 < l.size() && l.size() <= 2*n+1; j++) {
                                if (!e[l[j+1]][l[j]]) {
                                    ok = false;
                                    break;
                                }
                                auto &f = v[l[j+1]][l[j]];
                                l.insert(l.end(), f.rbegin(), f.rend());
                            }
                            if (!ok || l.size() > 2*n+1) {
                                break;
                            }
                        }
                        
                        r.assign(v[x][y].begin() + i, v[x][y].end());
                        if (!r.empty()) {
                            bool ok = true;
                            for (int j = 0; j+1 < r.size() && r.size() <= 2*n+1; j++) {
                                if (!e[r[j]][r[j+1]]) {
                                    ok = false;
                                    break;
                                }
                                auto &f = v[r[j]][r[j+1]];
                                r.insert(r.end(), f.begin(), f.end());
                            }
                            if (!ok || r.size() > 2*n+1) {
                                break;
                            }
                        }
                        
                        f[!l.empty()][!r.empty()].emplace_back(l.empty() ? x : l.back(), r.empty() ? y : r.back(), l.size() + r.size());
                    }
                }
            }
        }
    }
    
    // for (int i = 0; i < 2; i++) {
    //     for (int j = 0; j < 2; j++) {
    //         for (auto [x, y, l] : f[i][j]) {
    //             std::cerr << i << " " << j << " " << x+1 << " " << y+1 << " " << l << "\n";
    //         }
    //     }
    // }
    
    std::vector dp(2*n+2, std::vector(n, std::array<Z, 2>{}));
    for (int i = 0; i < n; i++) {
        dp[0][i][0] = 1;
    }
    std::vector<Z> ans(2*n+2);
    for (int i = 0; i <= 2*n+1; i++) {
        for (int u = 0; u < 2; u++) {
            for (int v = 0; v < 2; v++) {
                for (auto [x, y, l] : f[u][v]) {
                    if (i+l <= 2*n+1) {
                        dp[i+l][y][v] += dp[i][x][!u];
                    }
                }
            }
        }
        for (int x = 0; x < n; x++) {
            ans[i] += dp[i][x][1];
        }
    }
    for (int i = 2; i <= 2*n+1; i++) {
        std::cout << ans[i] << "\n";
    }
    
    return 0;
}
