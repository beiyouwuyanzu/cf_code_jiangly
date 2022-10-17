//url:https://codeforces.com/contest/1694/problem/A
//time:2022-06-27 11:15:56
//name:A-Creep

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int a, b;
    std::cin >> a >> b;
    
    std::string s;
    for (int i = 0; i < std::max(a, b); i++) {
        if (i < a) {
            s += '0';
        }
        if (i < b) {
            s += '1';
        }
    }
    
    std::cout << s << "\n";
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

