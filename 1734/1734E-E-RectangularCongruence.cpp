//url:https://codeforces.com/contest/1734/problem/E
//time:2022-09-23 15:48:51
//name:E-RectangularCongruence

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a = (i * j + b[i] - i * i) % n;
            if (a < 0) {
                a += n;
            }
            std::cout << a << " \n"[j == n - 1];
        }
    }
    
    return 0;
}
