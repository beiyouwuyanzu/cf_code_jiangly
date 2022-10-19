// url:https://codeforces.com/contest/492/problem/B
// time:2021-06-24 18:45:25
// name:B-VanyaandLanterns

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, l;
    std::cin >> n >> l;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    int ans = 2 * std::max(a[0], l - a.back());
    for (int i = 0; i < n - 1; i++) {
        ans = std::max(a[i + 1] - a[i], ans);
    }
    std::cout << ans / 2 << "." << "05"[ans % 2] << "\n";
    return 0;
}
