//url:https://codeforces.com/contest/765/problem/B
//time:2021-07-12 14:48:26
//name:B-Codeobfuscation

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    
    char x = 'a';
    for (auto c : s) {
        if (c > x) {
            std::cout << "NO\n";
            return 0;
        }
        
        if (c == x) {
            x++;
        }
    }
    
    std::cout << "YES\n";
    
    return 0;
}
