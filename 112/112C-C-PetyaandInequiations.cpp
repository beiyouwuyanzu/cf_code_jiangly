// url:https://codeforces.com/contest/112/problem/C
// time:2023-04-27 10:28:50
// name:C-PetyaandInequiations

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    i64 x, y;
    std::cin >> n >> x >> y;
    
    if (n > y || n - 1 + (y - n + 1) * (y - n + 1) < x) {
        std::cout << -1 << "\n";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        std::cout << (i ? 1 : y - n + 1) << "\n";
    }
    
    return 0;
}
