// url:https://codeforces.com/contest/1539/problem/B
// time:2021-06-20 13:17:43
// name:B-LoveSong

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> sum(n + 1);
    for (int i = 0; i < n; i++) {
        char c;
        std::cin >> c;
        sum[i + 1] = sum[i] + c - 'a' + 1;
    }
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--;
        std::cout << sum[r] - sum[l] << "\n";
    }
    return 0;
}
