// url:https://codeforces.com/contest/707/problem/A
// time:2023-03-15 09:07:05
// name:A-Brain'sPhotos

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            std::cin >> c;
            
            if (c == 'C' || c == 'M' || c == 'Y') {
                std::cout << "#Color\n";
                return 0;
            }
        }
    }
    
    std::cout << "#Black&White\n";
    
    return 0;
}

