//url:https://codeforces.com/contest/765/problem/C
//time:2021-07-12 14:51:49
//name:C-TableTennisGame2

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int k, a, b;
    std::cin >> k >> a >> b;
    
    if (a < k && b % k > 0) {
        std::cout << "-1\n";
        return 0;
    }
    
    if (b < k && a % k > 0) {
        std::cout << "-1\n";
        return 0;
    }
    
    std::cout << a / k + b / k << "\n";
    
    return 0;
}
