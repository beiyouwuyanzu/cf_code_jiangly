// url:https://codeforces.com/contest/487/problem/A
// time:2021-06-24 20:33:09
// name:A-FighttheMonster

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int HPY, ATKY, DEFY;
    std::cin >> HPY >> ATKY >> DEFY;
    int HPM, ATKM, DEFM;
    std::cin >> HPM >> ATKM >> DEFM;
    int h, a, d;
    std::cin >> h >> a >> d;
    int ans = 1e9;
    for (int ca = 0; ca <= 200; ca++) {
        for (int cd = 0; cd <= 100; cd++) {
            int ATK = ATKY + ca;
            int DEF = DEFY + cd;
            if (ATK <= DEFM) {
                continue;
            }
            if (DEF >= ATKM) {
                ans = std::min(ans, ca * a + cd * d);
            } else {
                ans = std::min(ans, h * std::max(0, ((HPM - 1) / (ATK - DEFM) + 1) * (ATKM - DEF) + 1 - HPY) + ca * a + cd * d);
            }
        }
    }
    std::cout << ans << "\n";
    return 0;
}
