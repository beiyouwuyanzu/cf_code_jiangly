//url:https://codeforces.com/contest/1085/problem/D
//time:2021-07-15 11:30:33
//name:D-MinimumDiameterTree

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, s;
    std::cin >> n >> s;
    
    std::vector<int> deg(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v--;
        deg[u]++;
        deg[v]++;
    }
    
    int leaves = std::count(deg.begin(), deg.end(), 1);
    
    double ans = 2.0 * s / leaves;
    
    std::cout << std::fixed << std::setprecision(10) << ans << "\n";
    
    return 0;
}
