// url:https://codeforces.com/contest/1530/problem/B
// time:2021-07-17 17:40:54
// name:B-PuttingPlates

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int n, m;
        std::cin >> n >> m;
        
        std::vector<std::string> s(n, std::string(m, '0'));
        for (int i = 0; i < m; i += 2) {
            s[0][i] = '1';
        }
        for (int i = 1; i < n; i++) {
            if (s[i - 1][m - 1] != '1' && s[i - 1][m - 2] != '1') {
                s[i][m - 1] = '1';
            }
        }
        for (int i = m - 2; i >= 0; i--) {
            if (s[n - 1][i + 1] != '1' && s[n - 2][i + 1] != '1') {
                s[n - 1][i] = '1';
            }
        }
        for (int i = n - 2; i > 1; i--) {
            if (s[i + 1][0] != '1' && s[i + 1][1] != '1') {
                s[i][0] = '1';
            }
        }
        
        for (int i = 0; i < n; i++) {
            std::cout << s[i] << "\n";
        }
    }
    
    return 0;
}
