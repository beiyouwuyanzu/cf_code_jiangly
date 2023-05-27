// url:https://codeforces.com/contest/112/problem/B
// time:2023-04-27 10:26:58
// name:B-PetyaandSquare

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, x, y;
    std::cin >> n >> x >> y;
    
    if ((x == n/2 || x == n/2+1) && (y == n/2 || y == n/2+1)) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }
    
    return 0;
}
