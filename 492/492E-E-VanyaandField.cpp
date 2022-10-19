// url:https://codeforces.com/contest/492/problem/E
// time:2021-06-24 18:33:03
// name:E-VanyaandField

#include <bits/stdc++.h>
using i64 = long long;
int inverse(int a, int m) {
    int g = m, r = a, x = 0, y = 1;
    while (r != 0) {
        int q = g / r;
        g %= r;
        std::swap(g, r);
        x -= q * y;
        std::swap(x, y);
    }
    return x < 0 ? x + m : x;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, dx, dy;
    std::cin >> n >> m >> dx >> dy;
    int px = inverse(dx, n);
    int py = inverse(dy, n);
    std::vector<int> cnt(n);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        int v = (i64(x) * px + i64(y) * (n - py)) % n;
        cnt[v]++;
    }
    int s = std::max_element(cnt.begin(), cnt.end()) - cnt.begin();
    std::cout << i64(s) * dx % n << " 0\n";
    return 0;
}
