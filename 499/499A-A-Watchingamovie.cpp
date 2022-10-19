// url:https://codeforces.com/contest/499/problem/A
// time:2021-06-21 22:20:12
// name:A-Watchingamovie

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, x;
    std::cin >> n >> x;
    int last = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;
        l--;
        ans += r - l;
        ans += (l - last) % x;
        last = r;
    }
    std::cout << ans << "\n";
    return 0;
}
