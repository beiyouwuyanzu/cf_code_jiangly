// url:https://codeforces.com/contest/1662/problem/K
// time:2022-04-24 17:17:28
// name:K-PandemicRestrictions

#include <bits/stdc++.h>

using i64 = long long;

using Point = std::complex<double>;

#define x real
#define y imag

double norm(const Point &a) {
    return std::sqrt(a.x() * a.x() + a.y() * a.y());
}

double dist(const Point &a, const Point &b) {
    return norm(a - b);
}

constexpr double eps = 1E-7;

double get(const Point &a, const Point &b, const Point &c) {
    double t = dist(a, b) + dist(b, c) + dist(c, a);
    
    Point ans = a;
    
    while (t > eps) {
        Point d;
        for (auto p : {a, b, c}) {
            if (dist(ans, p) > eps) {
                d += (ans - p) / dist(ans, p);
            }
        }
        ans -= d * t;
        t *= 0.9;
    }
    
    return dist(a, ans) + dist(b, ans) + dist(c, ans);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    Point p[3];
    for (int i = 0; i < 3; i++) {
        int x, y;
        std::cin >> x >> y;
        p[i] = Point(x, y);
    }
    
    Point ans = p[0];
    double t = 1;
    
    double res = 1E9;
    while (t > eps) {
        double f[3];
        f[0] = get(ans, p[0], p[1]);
        f[1] = get(ans, p[1], p[2]);
        f[2] = get(ans, p[2], p[0]);
        res = std::min(res, std::max({f[0], f[1], f[2]}));
        if (f[0] <= f[1] && f[0] <= f[2]) {
            ans -= t * (ans - p[2]);
        } else if (f[1] <= f[0] && f[1] <= f[2]) {
            ans -= t * (ans - p[0]);
        } else {
            ans -= t * (ans - p[1]);
        }
        t *= 0.9;
    }
    
    std::cout << std::fixed << std::setprecision(10) << res << "\n";
    
    return 0;
}
