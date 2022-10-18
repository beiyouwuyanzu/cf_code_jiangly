//url:https://codeforces.com/contest/1470/problem/A
//time:2021-01-05 17:38:48
//name:A-StrangeBirthdayParty

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
        int n, m;
        std::cin >> n >> m;
        std::vector<int> k(n);
        for (int i = 0; i < n; i++) {
            std::cin >> k[i];
            k[i]--;
        }
        std::vector<int> c(m);
        for (int i = 0; i < m; i++) {
            std::cin >> c[i];
        }
        std::sort(k.begin(), k.end());
        i64 ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            ans += c[std::min(k[i], n - 1 - i)];
        }
        std::cout << ans << "\n";
    }
    return 0;
}
