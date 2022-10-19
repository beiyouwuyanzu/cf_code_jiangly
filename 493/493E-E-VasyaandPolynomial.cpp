// url:https://codeforces.com/contest/493/problem/E
// time:2021-06-21 21:02:07
// name:E-VasyaandPolynomial

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    i64 t, a, b;
    std::cin >> t >> a >> b;
    if (t == 1) {
        if (a == 1) {
            if (b == 1) {
                std::cout << "inf\n";
            } else {
                std::cout << "0\n";
            }
            return 0;
        }
        i64 sum = 0, x = b;
        while (x) {
            sum += x % a;
            x /= a;
        }
        std::cout << (sum == a || (sum == 1 && b != 1)) << "\n";
    } else if (a == 1) {
        std::cout << (b == 1) << "\n";
    } else {
        int ans = 0;
        if (a == b) {
            ans++;
        }
        std::vector<i64> d;
        while (b) {
            d.push_back(b % a);
            b /= a;
        }
        i64 pt = 0, p = 1;
        for (int i = 0; i < int(d.size()); i++) {
            pt = std::min<__int128>(a + 1, pt + __int128(p) * d[i]);
            p = std::min<__int128>(a + 1, __int128(p) * t);
        }
        if (pt == a) {
            ans++;
        }
        std::cout << ans << "\n";
    }
    return 0;
}
