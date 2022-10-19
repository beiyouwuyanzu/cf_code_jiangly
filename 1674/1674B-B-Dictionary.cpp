// url:https://codeforces.com/contest/1674/problem/B
// time:2022-05-02 17:43:50
// name:B-Dictionary

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int a = s[0] - 'a';
    int b = s[1] - 'a';
    
    std::cout << a * 25 + b - (b > a) + 1 << "\n";
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
