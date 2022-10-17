//url:https://codeforces.com/contest/1726/problem/H
//time:2022-09-28 11:40:25
//name:H-MainakandtheBleedingPolygon

#include <bits/stdc++.h>

using i64 = long long;

constexpr long double Pi = std::acos(-1.L);

long double calc1(long double a) {
    return (1.L / std::tan(a) + (Pi - a) * (1.L / std::sin(a) / std::sin(a) + 2)) / 16.L;
}

constexpr long double eps = 1E-9;

long double ttox(long double a, long double t) {
    return (std::sin(t - a) + std::cos(t - a) * std::sin(t) * std::cos(t)) / std::sin(a);
}

long double ttoy(long double a, long double t) {
    return std::cos(t - a) * std::sin(t) * std::sin(t) / std::sin(a);
}

long double ytot(long double a, long double y) {
    long double low = a, high = Pi;
    while (high - low > eps) {
        const long double t = (low + high) / 2;
        const long double ty = ttoy(a, t);
        if (ty > y) {
            low = t;
        } else {
            high = t;
        }
    }
    
    return low;
}

long double ytox(long double a, long double y) {
    return ttox(a, ytot(a, y));
}

long double integrate(long double a, long double t) {
    return (std::sin(2 * (a - 3 * t)) - std::sin(2 * (a - 2 * t)) - 4 * std::sin(2 * (a - t)) - std::sin(2 * (a + t))
            - 4 * t * std::cos(2 * a) + 8 * t - 2 * std::sin(4 * t)) / 64.L / std::sin(a) / std::sin(a);
}

long double integrate(long double a, long double l, long double r) {
    return integrate(a, r) - integrate(a, l);
}

long double calc2(long double L, long double a1, long double a2) {
    long double low = 0, high = std::sin(std::max(a1, a2));
    
    while (high - low > eps) {
        const long double y = (low + high) / 2;
        
        if (ytox(a1, y) + ytox(a2, y) > L) {
            low = y;
        } else {
            high = y;
        }
    }
    
    const long double y = low;
    
    return integrate(a1, ytot(a1, y), Pi) + integrate(a2, ytot(a2, y), Pi);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::cout << std::fixed << std::setprecision(10);
    
    int n;
    std::cin >> n;
    
    std::vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    
    std::vector<long double> len(n), ang(n);
    for (int i = 0; i < n; i++) {
        const int j = (i + 1) % n;
        len[i] = std::sqrt(1LL * (x[i] - x[j]) * (x[i] - x[j]) + 1LL * (y[i] - y[j]) * (y[i] - y[j]));
    }
    
    if (n == 4 && ((len[0] == 1 && len[2] == 1) || (len[1] == 1 && len[3] == 1))) {
        std::cout << len[0] * len[1] << "\n";
        return 0;
    }
    
    for (int i = 0; i < n; i++) {
        const int l = (i - 1 + n) % n;
        const int r = (i + 1) % n;
        ang[i] = std::acos((1LL * (x[l] - x[i]) * (x[r] - x[i]) + 1LL * (y[l] - y[i]) * (y[r] - y[i])) / len[l] / len[i]);
    }
    
    long double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += calc1(ang[i]);
    }
    
    for (int i = 0; i < n; i++) {
        if (len[i] < 2) {
            const int j = (i + 1) % n;
            ans -= calc2(len[i], ang[i], ang[j]);
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
