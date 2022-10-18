//url:https://codeforces.com/contest/1472/problem/B
//time:2021-01-04 17:38:53
//name:B-FairDivision

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
        int one = 0, two = 0;
        for (int i = 0; i < n; i++) {
            int a;
            std::cin >> a;
            if (a == 1) {
                one++;
            } else {
                two++;
            }
        }
        int total = one + 2 * two;
        if (total % 2 == 0 && (total % 4 == 0 || one > 0)) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
