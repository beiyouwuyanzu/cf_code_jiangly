// url:https://codeforces.com/contest/1515/problem/D
// time:2021-05-02 17:49:02
// name:D-PhoenixandSocks

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
        int n, l, r;
        std::cin >> n >> l >> r;
        std::vector<int> c(n);
        std::vector<int> cntl(n), cntr(n);
        for (int i = 0; i < n; i++) {
            std::cin >> c[i];
            c[i]--;
            if (i < l) {
                cntl[c[i]]++;
            } else {
                cntr[c[i]]++;
            }
        }
        int matchl = 0, matchr = 0;
        for (int i = 0; i < n; i++) {
            int m = std::min(cntl[i], cntr[i]);
            cntl[i] -= m;
            cntr[i] -= m;
            l -= m;
            r -= m;
            matchl += cntl[i] / 2;
            matchr += cntr[i] / 2;
        }
        int ans = (l + r) / 2 + std::max({0, (l - r) / 2 - matchl, (r - l) / 2 - matchr});
        std::cout << ans << "\n";
    }
    return 0;
}
