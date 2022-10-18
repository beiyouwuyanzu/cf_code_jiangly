//url:https://codeforces.com/contest/1503/problem/A
//time:2021-04-03 17:39:54
//name:A-BalancetheBits

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::string a;
        std::cin >> a;
        int c1 = std::count(a.begin(), a.end(), '1');
        if (a[0] == '0' || a[n - 1] == '0' || std::count(a.begin(), a.end(), '0') % 2 != 0) {
            std::cout << "NO\n";
            continue;
        }
        std::string s, t;
        int k = 0, b = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == '1') {
                if (k < c1 / 2) {
                    s += '(';
                    t += '(';
                } else {
                    s += ')';
                    t += ')';
                }
                k++;
            } else {
                if (b % 2 == 0) {
                    s += '(';
                    t += ')';
                } else {
                    s += ')';
                    t += '(';
                }
                b++;
            }
        }
        std::cout << "YES\n";
        std::cout << s << "\n";
        std::cout << t << "\n";
    }
    return 0;
}

