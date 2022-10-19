// url:https://codeforces.com/contest/498/problem/A
// time:2021-06-21 21:15:47
// name:A-CrazyTown

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    int ans = 0;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        i64 A = i64(a) * x1 + i64(b) * y1 + c;
        i64 B = i64(a) * x2 + i64(b) * y2 + c;
        if ((A > 0) != (B > 0)) {
            ans++;
        }
    }
    std::cout << ans << "\n";
    return 0;
}
