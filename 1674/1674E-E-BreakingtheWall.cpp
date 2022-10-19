// url:https://codeforces.com/contest/1674/problem/E
// time:2022-05-02 17:52:36
// name:E-BreakingtheWall

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        b[i] = (a[i] + 1) / 2;
    }
    std::nth_element(b.begin(), b.begin() + 2, b.end());
    
    int ans = b[0] + b[1];
    
    for (int i = 0; i < n - 1; i++) {
        ans = std::min(ans, std::max({(a[i] + 1) / 2, (a[i + 1] + 1) / 2, (a[i] + a[i + 1] + 2) / 3}));
    }
    for (int i = 0; i < n - 2; i++) {
        ans = std::min(ans, 1 + a[i] / 2 + a[i + 2] / 2);
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
