// url:https://codeforces.com/contest/1742/problem/D
// time:2022-10-13 17:59:06
// name:D-Coprime

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> last(1001);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        last[x] = i + 1;
    }
    
    int ans = -1;
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= i; j++) {
            if (last[i] && last[j] && std::gcd(i, j) == 1) {
                ans = std::max(ans, last[i] + last[j]);
            }
        }
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

