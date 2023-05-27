// url:https://codeforces.com/contest/1812/problem/B
// time:2023-04-01 17:52:19
// name:B-WasitRated?

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    if (n == 15 || n == 20 || n == 21) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }
    
    return 0;
}
