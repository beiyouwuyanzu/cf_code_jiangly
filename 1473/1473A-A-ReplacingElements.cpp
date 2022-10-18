//url:https://codeforces.com/contest/1473/problem/A
//time:2021-01-14 17:39:00
//name:A-ReplacingElements

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
        int n, d;
        std::cin >> n >> d;
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        std::sort(a.begin(), a.end());
        if (a[0] + a[1] <= d || a[n - 1] <= d) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
