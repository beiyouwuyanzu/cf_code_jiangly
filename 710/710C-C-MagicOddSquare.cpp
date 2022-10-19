// url:https://codeforces.com/contest/710/problem/C
// time:2021-07-07 22:14:08
// name:C-MagicOddSquare

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    int m = (n - 1) / 2;
    int odd = 1, even = 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            if (std::abs(i - m) + std::abs(j - m) <= m) {
                x = odd;
                odd += 2;
            } else {
                x = even;
                even += 2;
            }
            std::cout << x << " \n"[j == n - 1];
        }
    }
    
    return 0;
}
