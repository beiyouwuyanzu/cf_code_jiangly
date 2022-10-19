// url:https://codeforces.com/contest/1543/problem/B
// time:2021-07-07 17:38:57
// name:B-CustomisingtheTrack

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
        i64 sum = 0;
        for (int i = 0; i < n; i++) {
            int x;
            std::cin >> x;
            sum += x;
        }
        
        std::cout << sum % n * (n - sum % n) << "\n";
    }
    
    return 0;
}
