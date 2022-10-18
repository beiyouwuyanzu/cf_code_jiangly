//url:https://codeforces.com/contest/708/problem/B
//time:2021-12-24 04:50:52
//name:B-RecovertheString

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int a00, a01, a10, a11;
    std::cin >> a00 >> a01 >> a10 >> a11;
    
    int c0 = 0, c1 = 0;
    while (c0 * (c0 - 1) / 2 < a00) {
        c0++;
    }
    while (c1 * (c1 - 1) / 2 < a11) {
        c1++;
    }
    
    for (auto c0 : {c0, 1}) {
        for (auto c1 : {c1, 1}) {
            if (c0 * (c0 - 1) / 2 != a00 || c1 * (c1 - 1) / 2 != a11) {
                continue;
            }
            if (a01 + a10 != 1LL * c0 * c1) {
                continue;
            }
            if (c0 + c1 == 0) {
                continue;
            }
            if (c0 == 0 || c1 == 0) {
                std::cout << std::string(c0, '0') + std::string(c1, '1') << "\n";
            } else {
                int r = a01 / c0;
                int l = c1 - r;
                
                std::string ans = std::string(c0, '0') + std::string(r, '1');
                if (a01 % c0 != 0) {
                    l--;
                    ans.insert(ans.begin() + a01 % c0, '1');
                }
                ans = std::string(l, '1') + ans;
                std::cout << ans << "\n";
            }
            return 0;
        }
    }
    
    std::cout << "Impossible\n";
    
    return 0;
}
