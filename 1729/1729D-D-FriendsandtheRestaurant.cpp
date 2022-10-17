//url:https://codeforces.com/contest/1729/problem/D
//time:2022-09-12 17:45:58
//name:D-FriendsandtheRestaurant

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        int y;
        std::cin >> y;
        x[i] = y - x[i];
    }
    
    std::sort(x.begin(), x.end());
    
    int p = std::lower_bound(x.begin(), x.end(), 0) - x.begin();
    int ans = 0;
    for (int i = 0, j = n - 1; i < p; i++) {
        if (j >= p && x[i] + x[j] >= 0) {
            ans++;
            j--;
        }
    }
    ans += (n - p - ans) / 2;
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
