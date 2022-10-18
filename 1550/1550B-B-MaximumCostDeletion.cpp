//url:https://codeforces.com/contest/1550/problem/B
//time:2021-07-14 17:40:45
//name:B-MaximumCostDeletion

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int n, a, b;
        std::cin >> n >> a >> b;
        
        std::string s;
        std::cin >> s;
        
        int cnt = 1;
        for (int i = 1; i < n; i++) {
            if (s[i] != s[i - 1]) {
                cnt++;
            }
        }
        
        int ans = a * n + std::max(n * b, (cnt / 2 + 1) * b);
        
        std::cout << ans << "\n";
    }
    
    return 0;
}
