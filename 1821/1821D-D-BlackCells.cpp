// url:https://codeforces.com/contest/1821/problem/D
// time:2023-04-20 19:14:58
// name:D-BlackCells

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        std::cin >> l[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> r[i];
    }
    
    int sum = 0;
    int ans = 2E9;
    std::priority_queue<int, std::vector<int>, std::greater<>> h;
    for (int i = 0; i < n; i++) {
        sum += r[i] - l[i] + 1;
        h.push(r[i] - l[i] + 1);
        while (sum >= k) {
            int t = k - (sum - (r[i] - l[i] + 1)) + l[i] - 1;
            ans = std::min(ans, 2 * int(h.size()) + t);
            sum -= h.top();
            h.pop();
        }
    }
    
    if (ans == 2E9) {
        ans = -1;
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
