// url:https://codeforces.com/contest/609/problem/C
// time:2023-04-24 08:23:26
// name:C-LoadBalancing

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> m(n);
    for (int i = 0; i < n; i++) {
        std::cin >> m[i];
    }
    
    int sum = std::accumulate(m.begin(), m.end(), 0);
    int lo = sum / n;
    int hi = (sum+n-1) / n;
    
    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (m[i] < lo) {
            l += lo - m[i];
        }
        if (m[i] > hi) {
            r += m[i] - hi;
        }
    }
    int ans = std::max(l, r);
    
    std::cout << ans << "\n";
    
    return 0;
}
