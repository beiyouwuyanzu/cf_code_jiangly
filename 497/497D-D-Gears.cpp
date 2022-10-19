// url:https://codeforces.com/contest/497/problem/D
// time:2021-06-20 19:49:21
// name:D-Gears

#include <bits/stdc++.h>
using i64 = long long;
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    Point &operator+=(const Point &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    Point &operator-=(const Point &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    friend Point operator+(const Point &lhs, const Point &rhs) {
        return Point(lhs.x + rhs.x, lhs.y + rhs.y);
    }
    friend Point operator-(const Point &lhs, const Point &rhs) {
        return Point(lhs.x - rhs.x, lhs.y - rhs.y);
    }
    int len() const {
        return x * x + y * y;
    }
};
int dot(const Point &a, const Point &b) {
    return a.x * b.x + a.y * b.y;
}
int cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
void yes() {
    std::cout << "YES\n";
    std::exit(0);
}
void check(Point p, Point a0, Point a1, Point q, Point b) {
    p += b - q;
    a0 -= p;
    a1 -= p;
    b -= p;
    if (a0.len() < b.len() && a1.len() < b.len()) {
        return;
    }
    if (a0.len() >= b.len() && a1.len() >= b.len()) {
        int area = std::abs(cross(a0, a1));
        if (dot(a0 - a1, a0) >= 0 && dot(a1 - a0, a1) >= 0 && i64(area) * area <= i64((a1 - a0).len()) * b.len()) {
            yes();
        } else {
            return;
        }
    }
    yes();
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Point p, q;
    int n, m;
    std::cin >> p.x >> p.y;
    std::cin >> n;
    std::vector<Point> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i].x >> a[i].y;
    }
    std::cin >> q.x >> q.y;
    std::cin >> m;
    std::vector<Point> b(m);
    for (int i = 0; i < m; i++) {
        std::cin >> b[i].x >> b[i].y;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            check(p, a[i], a[(i + 1) % n], q, b[j]);
            check(q, b[j], b[(j + 1) % m], p, a[i]);
        }
    }
    std::cout << "NO\n";
    return 0;
}
