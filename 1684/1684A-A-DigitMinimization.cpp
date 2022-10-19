// url:https://codeforces.com/contest/1684/problem/A
// time:2022-05-19 17:36:55
// name:A-DigitMinimization

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    if (n < 100) {
        std::cout << n % 10 << "\n";
    } else {
        auto s = std::to_string(n);
        std::cout << *std::min_element(s.begin(), s.end()) << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
