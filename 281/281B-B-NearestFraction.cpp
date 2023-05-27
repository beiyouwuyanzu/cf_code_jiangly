// url:https://codeforces.com/contest/281/problem/B
// time:2023-04-28 20:43:53
// name:B-NearestFraction

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    i64 x, y, n;
    std::cin >> x >> y >> n;
    
    i64 a = 0, b = 1;
    for (int j = 1; j <= n; j++) {
        i64 t = x * j / y;
        for (auto i : {t, t + 1}) {
            if (std::abs(i * b * y - x * b * j) < std::abs(a * j * y - x * b * j)) {
                a = i;
                b = j;
            }
        }
    }
    std::cout << a << "/" << b << "\n";
    
    return 0;
}
