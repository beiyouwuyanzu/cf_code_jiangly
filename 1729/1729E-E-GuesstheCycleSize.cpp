//url:https://codeforces.com/contest/1729/problem/E
//time:2022-09-12 17:49:50
//name:E-GuesstheCycleSize

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    for (int i = 1; ; i++) {
        for (int j = 1; j < i; j++) {
            i64 x, y;
            std::cout << "? " << i << " " << j << std::endl;
            std::cin >> x;
            std::cout << "? " << j << " " << i << std::endl;
            std::cin >> y;
            if (x == -1 || y == -1) {
                std::cout << "! " << i - 1 << std::endl;
                return 0;
            }
            if (x != y) {
                std::cout << "! " << x + y << std::endl;
                return 0;
            }
        }
    }
    
    return 0;
}
