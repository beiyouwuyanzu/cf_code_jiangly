// url:https://codeforces.com/contest/1485/problem/B
// time:2021-02-12 17:57:40
// name:B-ReplaceandKeepSorted

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q, k;
    std::cin >> n >> q >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--;
        r--;
        std::cout << a[r] - a[l] + k + 1 - 2 * (r - l + 1) << "\n";
    }
    return 0;
}
