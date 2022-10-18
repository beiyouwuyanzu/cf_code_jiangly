//url:https://codeforces.com/contest/1550/problem/C
//time:2021-07-14 17:45:08
//name:C-ManhattanSubarrays

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        
        auto isGood = [&](int l, int r) {
            for (int i = l; i <= r; i++) {
                for (int j = i + 1; j <= r; j++) {
                    for (int k = j + 1; k <= r; k++) {
                        if (a[i] >= a[j] && a[j] >= a[k]) {
                            return false;
                        }
                        if (a[i] <= a[j] && a[j] <= a[k]) {
                            return false;
                        }
                    }
                }
            }
            
            return true;
        };
        
        int ans = 0;
        for (int i = 0, j = 0; i < n; i++) {
            while (!isGood(j, i)) {
                j++;
            }
            
            ans += i - j + 1;
        }
        
        std::cout << ans << "\n";
    }
    
    return 0;
}
