// url:https://codeforces.com/contest/235/problem/A
// time:2023-04-30 12:04:59
// name:A-LCMChallenge

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    if (n <= 2) {
        std::cout << n << "\n";
    } else if (n % 2) {
        std::cout << 1LL * n * (n - 1) * (n - 2) << "\n";
    } else if (n % 3) {
        std::cout << 1LL * n * (n - 1) * (n - 3) << "\n";
    } else {
        std::cout << 1LL * (n - 1) * (n - 2) * (n - 3) << "\n";
    }
    
    return 0;
}
