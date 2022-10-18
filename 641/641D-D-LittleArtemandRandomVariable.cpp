//url:https://codeforces.com/contest/641/problem/D
//time:2021-07-09 22:13:12
//name:D-LittleArtemandRandomVariable

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<double> mx(n), mn(n);
    for (int i = 0; i < n; i++) {
        std::cin >> mx[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> mn[i];
    }
    
    for (int i = 1; i < n; i++) {
        mx[i] += mx[i - 1];
    }
    for (int i = n - 2; i >= 0; i--) {
        mn[i] += mn[i + 1];
    }
    
    std::vector<double> a(n), b(n);
    for (int i = 0; i < n - 1; i++) {
        double s = mx[i] - mn[i + 1] + 1;
        double r = std::sqrt(std::max(0.0, s * s - 4 * mx[i]));
        a[i] = (s - r) / 2;
        b[i] = (s + r) / 2;
    }
    a[n - 1] = b[n - 1] = 1;
    for (int i = n - 1; i > 0; i--) {
        a[i] -= a[i - 1];
        b[i] -= b[i - 1];
    }
    
    std::cout << std::fixed << std::setprecision(10);
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " \n"[i == n - 1];
    }
    for (int i = 0; i < n; i++) {
        std::cout << b[i] << " \n"[i == n - 1];
    }
    
    return 0;
}
