//url:https://codeforces.com/contest/641/problem/A
//time:2021-07-09 22:03:49
//name:A-LittleArtemandGrasshopper

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    std::vector<int> d(n);
    for (int i = 0; i < n; i++) {
        std::cin >> d[i];
    }
    
    int p = 0;
    for (int t = 0; t < n; t++) {
        if (s[p] == '<') {
            p -= d[p];
        } else {
            p += d[p];
        }
        if (p < 0 || p >= n) {
            std::cout << "FINITE\n";
            return 0;
        }
    }
    
    std::cout << "INFINITE\n";
    
    return 0;
}
