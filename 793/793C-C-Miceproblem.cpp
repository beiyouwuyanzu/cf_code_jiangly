//url:https://codeforces.com/contest/793/problem/C
//time:2021-01-03 17:42:48
//name:C-Miceproblem

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    double L = 0, R = 1e9;
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    auto work = [&](int s, int v, int l, int r) {
        if (v > 0) {
            L = std::max(L, double(l - s) / v);
            R = std::min(R, double(r - s) / v);
        } else if (v < 0) {
            L = std::max(L, double(s - r) / -v);
            R = std::min(R, double(s - l) / -v);
        } else if (s <= l || s >= r) {
            R = -1;
        }
    };
    for (int i = 0; i < n; i++) {
        int rx, ry, vx, vy;
        std::cin >> rx >> ry >> vx >> vy;
        work(rx, vx, x1, x2);
        work(ry, vy, y1, y2);
    }
    if (L >= R) {
        std::cout << "-1\n";
    } else {
        std::cout << std::fixed << std::setprecision(10) << L << "\n";
    }
    return 0;
}

