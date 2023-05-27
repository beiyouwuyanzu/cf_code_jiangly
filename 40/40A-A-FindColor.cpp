// url:https://codeforces.com/contest/40/problem/A
// time:2023-04-23 06:38:10
// name:A-FindColor

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int x, y;
    std::cin >> x >> y;
    
    if (!x || !y) {
        std::cout << "black\n";
    } else {
        int z = x * x + y * y;
        int w = std::sqrt(z);
        if (w * w == z || ((w % 2) ^ (x < 0) ^ (y < 0)) == 0) {
            std::cout << "black\n";
        } else {
            std::cout << "white\n";
        }
    }
    
    return 0;
}
