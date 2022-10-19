// url:https://codeforces.com/contest/1619/problem/C
// time:2021-12-20 18:01:09
// name:C-WrongAddition

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    i64 a, s;
    std::cin >> a >> s;
    
    i64 b = 0, t = 1;
    
    while (s != 0) {
        int da = a % 10;
        int ds = s % 10;
        
        a /= 10;
        s /= 10;
        if (da <= ds) {
            b += t * (ds - da);
        } else if (s % 10 == 1) {
            s /= 10;
            b += t * (10 + ds - da);
        } else {
            std::cout << "-1\n";
            return;
        }
        
        t *= 10;
    }
    
    if (a == 0) {
        std::cout << b << "\n";
    } else {
        std::cout << "-1\n";
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

