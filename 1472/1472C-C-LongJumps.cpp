//url:https://codeforces.com/contest/1472/problem/C
//time:2021-01-04 17:40:17
//name:C-LongJumps

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        int ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (i + a[i] < n) {
                a[i] += a[i + a[i]];
            }
            ans = std::max(ans, a[i]);
        }
        std::cout << ans << "\n";
    }
    return 0;
}
