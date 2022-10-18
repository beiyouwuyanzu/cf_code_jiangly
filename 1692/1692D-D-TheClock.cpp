//url:https://codeforces.com/contest/1692/problem/D
//time:2022-06-14 17:43:30
//name:D-TheClock

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int x;
    std::cin >> x;
    
    x = std::gcd(x, 1440);
    
    int t = std::stoi(s.substr(0, 2)) * 60 + std::stoi(s.substr(3));
    t %= x;
    
    int ans = 0;
    for (int i = t; i < 1440; i += x) {
        int a = i / 600;
        int b = i / 60 % 10;
        int c = i / 10 % 6;
        int d = i % 10;
        
        if (a == d && b == c) {
            ans++;
        }
    }
    
    std::cout << ans << "\n";
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

