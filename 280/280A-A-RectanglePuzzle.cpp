// url:https://codeforces.com/contest/280/problem/A
// time:2023-04-30 08:40:32
// name:A-RectanglePuzzle

#include <bits/stdc++.h>

using i64 = long long;

constexpr double Pi = std::numbers::pi;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int w, h, a;
    std::cin >> w >> h >> a;
    
    if (w < h) {
        std::swap(w, h);
    }
    
    if (a > 90) {
        a = 180 - a;
    }
    
    double ang = Pi * a / 180;
    
    std::cout << std::fixed << std::setprecision(10);
    
    double ans;
    
    double t = std::atan(1. * h / w);
    double e = std::sqrt(1. * h * h + 1. * w * w);
    
    if (ang < 2 * t) {
        ans = 1. * w * h;
        if (ang > 0) {
            double r = e / 2 * std::sin(ang + t) - h / 2.;
            ans -= r * r / std::sin(ang) / std::cos(ang);
            r = e / 2 * std::sin(Pi / 2 - ang + t) - w / 2.;
            ans -= r * r / std::sin(ang) / std::cos(ang);
        }
    } else {
        ans = 1. * h * h / std::sin(ang);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
