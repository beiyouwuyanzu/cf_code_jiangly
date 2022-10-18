//url:https://codeforces.com/contest/702/problem/B
//time:2021-07-12 19:01:21
//name:B-PowersofTwo

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    i64 ans = 0;
    
    std::map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        
        for (int j = 1; j <= 30; j++) {
            if ((1 << j) > x && cnt.count((1 << j) - x)) {
                ans += cnt[(1 << j) - x];
            }
        }
        
        cnt[x]++;
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
