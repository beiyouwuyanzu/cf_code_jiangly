// url:https://codeforces.com/contest/1539/problem/C
// time:2021-06-20 13:21:28
// name:C-StableGroups

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    i64 k, x;
    std::cin >> n >> k >> x;
    int ans = 0;
    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    std::vector<i64> v;
    for (int i = 0; i < n - 1; i++) {
        v.push_back(std::max<i64>(0, a[i + 1] - a[i] - 1) / x);
    }
    std::sort(v.begin(), v.end());
    for (int i = 0; i < n - 1; i++) {
        if (k >= v[i]) {
            ans++;
            k -= v[i];
        }
    }
    std::cout << n - ans << "\n";
    return 0;
}
