//url:https://codeforces.com/contest/1700/problem/D
//time:2022-06-19 12:25:17
//name:D-RiverLocks

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i];
    }
    
    std::vector<i64> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + v[i];
    }
    
    i64 res = 0;
    for (int i = 1; i <= n; i++) {
        res = std::max(res, (sum[i] + i - 1) / i);
    }
    
    int q;
    std::cin >> q;
    
    for (int i = 0; i < q; i++) {
        int t;
        std::cin >> t;
        
        if (t < res) {
            std::cout << "-1\n";
        } else {
            std::cout << (sum[n] + t - 1) / t << "\n";
        }
    }
    
    return 0;
}

