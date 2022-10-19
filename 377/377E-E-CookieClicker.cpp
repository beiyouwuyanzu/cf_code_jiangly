// url:https://codeforces.com/contest/377/problem/E
// time:2021-06-19 21:53:19
// name:E-CookieClicker

#include <bits/stdc++.h>
using i64 = long long;
using Point = std::complex<__int128>;
#define x real
#define y imag
i64 cross(const Point &a, const Point &b) {
    return (std::conj(a) * b).y();
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    i64 s;
    std::cin >> n >> s;
    std::vector<std::pair<int, int>> a(n);
    i64 ans = s;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i].first >> a[i].second;
    }
    std::sort(a.begin(), a.end());
    for (int i = n - 2; i >= 0; i--) {
        a[i].second = std::min(a[i].second, a[i + 1].second);
    }
    std::vector<Point> hull;
    for (int i = 0, j = 0; i < n; i++) {
        auto [v, c] = a[i];
        int t, r;
        if (c == 0) {
            t = 0;
            r = 0;
        } else {
            t = (c - hull[j].y() + hull[j].x() - 1) / hull[j].x();
            while (j + 1 < int(hull.size()) && t * hull[j].x() + hull[j].y() <= t * hull[j + 1].x() + hull[j + 1].y()) {
                j++;
                t = (c - hull[j].y() + hull[j].x() - 1) / hull[j].x();
            }
            r = t * hull[j].x() + hull[j].y() - c;
        }
        ans = std::min(ans, t + (std::max<i64>(0, s - r) + v - 1) / v);
        i64 val = r - i64(t) * v;
        Point p(v, val);
        while (hull.size() >= 2 && cross(hull.back() - hull[hull.size() - 2], p - hull.back()) >= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }
    std::cout << ans << "\n";
    return 0;
}
