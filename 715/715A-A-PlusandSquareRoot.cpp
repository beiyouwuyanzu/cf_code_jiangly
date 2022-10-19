// url:https://codeforces.com/contest/715/problem/A
// time:2021-07-07 11:06:44
// name:A-PlusandSquareRoot

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    for (int i = 1; i <= n; i++) {
        std::cout << i64(i) * (i + 1) * (i + 1) - i + 1 - (i == 1 ? 2 : 0) << "\n";
    }
    
    return 0;
}
