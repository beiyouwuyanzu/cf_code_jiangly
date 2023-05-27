// url:https://codeforces.com/contest/158/problem/A
// time:2023-04-26 19:38:12
// name:A-NextRound

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a.begin(), a.end());
    
    int v = std::max(1, a[n-k]);
    int ans = a.end() - std::lower_bound(a.begin(), a.end(), v);
    std::cout << ans << "\n";
    
    return 0;
}
