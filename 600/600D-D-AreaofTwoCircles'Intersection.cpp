// url:https://codeforces.com/contest/600/problem/D
// time:2023-04-24 06:46:20
// name:D-AreaofTwoCircles'Intersection

#include <bits/stdc++.h>

using i64 = long long;

constexpr long double Pi = std::numbers::pi;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    long double x1, y1, r1;
    std::cin >> x1 >> y1 >> r1;
    
    long double x2, y2, r2;
    std::cin >> x2 >> y2 >> r2;
    
    long double d = std::sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    
    std::cout << std::fixed << std::setprecision(10);
    if (d >= r1+r2) {
        std::cout << 0. << "\n";
        return 0;
    }
    
    if (r1+d <= r2) {
        std::cout << Pi * r1 * r1 << "\n";
        return 0;
    }
    
    if (r2+d <= r1) {
        std::cout << Pi * r2 * r2 << "\n";
        return 0;
    }
    
    long double ans = 0;
    
    long double ang1 = std::acos((r1*r1 + d*d - r2*r2) / (2*r1*d));
    ans += ang1 * r1 * r1;
    ans -= r1*std::sin(ang1) * r1*std::cos(ang1);
    
    long double ang2 = std::acos((r2*r2 + d*d - r1*r1) / (2*r2*d));
    ans += ang2 * r2 * r2;
    ans -= r2*std::sin(ang2) * r2*std::cos(ang2);
    
    std::cout << ans << "\n";
    
    return 0;
}
