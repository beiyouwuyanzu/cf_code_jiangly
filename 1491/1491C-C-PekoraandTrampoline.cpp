// url:https://codeforces.com/contest/1491/problem/C
// time:2021-02-28 16:52:49
// name:C-PekoraandTrampoline

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
        std::vector<int> s(n);
        for (int i = 0; i < n; i++) {
            std::cin >> s[i];
        }
        i64 ans = 0;
        std::vector<i64> a(n);
        for (int i = 0; i < n; i++) {
            if (s[i] - a[i] > 1) {
                ans += s[i] - a[i] - 1;
                a[i] = s[i] - 1;
            }
            for (int j = i + 2; j <= std::min(n - 1, i + s[i]); j++) {
                a[j]++;
            }
            if (i + 1 < n) {
                a[i + 1] += a[i] - (s[i] - 1);
            }
        }
        std::cout << ans << "\n";
    }
    return 0;
}

