// url:https://codeforces.com/contest/710/problem/D
// time:2021-07-07 22:30:28
// name:D-TwoArithmeticProgressions

#include <bits/stdc++.h>

using i64 = long long;

i64 exgcd(i64 a, i64 b, i64 &x, i64 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 g = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

i64 divFloor(i64 a, i64 b) {
    if (a >= 0) {
        return a / b;
    } else {
        return (a - b + 1) / b;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    i64 a1, b1, a2, b2, L, R;
    std::cin >> a1 >> b1 >> a2 >> b2 >> L >> R;
    
    L = std::max({L, b1, b2});
    if (L > R) {
        std::cout << "0\n";
        return 0;
    }
    
    b1 = (b1 % a1 + a1) % a1;
    b2 = (b2 % a2 + a2) % a2;
    
    i64 x, y;
    i64 g = exgcd(a1, a2, x, y);
    
    if ((b1 - b2) % g != 0) {
        std::cout << "0\n";
        return 0;
    }
    
    i64 m = a1 * a2 / g;
    x = b1 + (b2 - b1) / g * x % a2 * a1;
    x = (x % m + m) % m;
    
    i64 ans = divFloor(R - x, m) - divFloor(L - 1 - x, m);
    std::cout << ans << "\n";
    
    return 0;
}
