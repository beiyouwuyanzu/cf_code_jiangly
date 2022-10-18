//url:https://codeforces.com/contest/793/problem/A
//time:2021-01-03 17:25:49
//name:A-Olegandshares

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        if (a[i] % k != a[0] % k) {
            std::cout << "-1\n";
            return 0;
        }
    }
    i64 sum = std::accumulate(a.begin(), a.end(), 0ll);
    int mn = *std::min_element(a.begin(), a.end());
    i64 ans = (sum - i64(n) * mn) / k;
    std::cout << ans << "\n";
    return 0;
}
