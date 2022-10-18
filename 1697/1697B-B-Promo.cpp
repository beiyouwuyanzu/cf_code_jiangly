//url:https://codeforces.com/contest/1697/problem/B
//time:2022-06-12 17:53:28
//name:B-Promo

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    
    std::sort(p.begin(), p.end());
    
    std::vector<i64> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + p[i];
    }
    
    for (int i = 0; i < q; i++) {
        int x, y;
        std::cin >> x >> y;
        
        std::cout << sum[n - (x - y)] - sum[n - x] << "\n";
    }
    
    return 0;
}

