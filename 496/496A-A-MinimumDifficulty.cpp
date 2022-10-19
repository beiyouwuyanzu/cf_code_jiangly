// url:https://codeforces.com/contest/496/problem/A
// time:2021-06-20 20:43:22
// name:A-MinimumDifficulty

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    int ans = 1e9;
    for (int i = 0; i < n - 2; i++) {
        ans = std::min(ans, a[i + 2] - a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
        ans = std::max(ans, a[i + 1] - a[i]);
    }
    std::cout << ans << "\n";
    return 0;
}
