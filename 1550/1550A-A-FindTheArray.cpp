//url:https://codeforces.com/contest/1550/problem/A
//time:2021-07-14 17:36:27
//name:A-FindTheArray

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int s;
        std::cin >> s;
        
        int x = 1;
        while (x * x < s) {
            x++;
        }
        
        std::cout << x << "\n";
    }
}
