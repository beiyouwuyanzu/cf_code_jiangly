//url:https://codeforces.com/contest/1574/problem/C
//time:2022-06-12 07:27:19
//name:C-SlaytheDragon

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n;
    
    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a.begin(), a.end());
    
    i64 sum = std::accumulate(a.begin(), a.end(), 0LL);
    
    std::cin >> m;
    
    for (int i = 0; i < m; i++) {
        i64 x, y;
        std::cin >> x >> y;
        
        i64 ans = x + y;
        
        int j = std::lower_bound(a.begin(), a.end(), x) - a.begin();
        
        if (j < n) {
            ans = std::min(ans, std::max(0LL, y - (sum - a[j])));
        }
        
        j--;
        if (j >= 0) {
            ans = std::min(ans, x - a[j] + std::max(0LL, y - (sum - a[j])));
        }
        
        std::cout << ans << "\n";
    }
    
    return 0;
}

