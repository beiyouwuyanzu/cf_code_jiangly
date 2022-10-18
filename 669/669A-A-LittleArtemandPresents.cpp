//url:https://codeforces.com/contest/669/problem/A
//time:2021-07-09 23:29:12
//name:A-LittleArtemandPresents

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::cout << (n / 3 * 2 + (n % 3 > 0)) << "\n";
    
    return 0;
}
