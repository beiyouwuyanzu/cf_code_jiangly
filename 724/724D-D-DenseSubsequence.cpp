// url:https://codeforces.com/contest/724/problem/D
// time:2021-12-23 17:45:21
// name:D-DenseSubsequence

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int m;
    std::cin >> m;
    
    std::string s;
    std::cin >> s;
    
    int n = s.length();
    
    std::string ans;
    for (int c = 'a'; c <= 'z'; c++) {
        int j = -1;
        bool nice = true;
        for (int i = 0; i < n; i++) {
            if (s[i] <= c) {
                if (i - j > m) {
                    nice = false;
                }
                j = i;
            }
        }
        if (n - j > m) {
            nice = false;
        }
        if (!nice) {
            for (int i = 0; i < n; i++) {
                if (s[i] == c) {
                    ans += c;
                }
            }
            continue;
        }
        
        j = -1;
        int k = -1;
        for (int i = 0; i < n; i++) {
            if (s[i] < c) {
                j = i;
            } else if (s[i] == c) {
                k = i;
            }
            if (i - j >= m) {
                j = k;
                ans += c;
            }
        }
        
        break;
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
