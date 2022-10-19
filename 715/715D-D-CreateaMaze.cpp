// url:https://codeforces.com/contest/715/problem/D
// time:2021-07-07 15:30:54
// name:D-CreateaMaze

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    i64 T;
    std::cin >> T;
    
    const int d = 24;
    std::vector<int> a(d);
    for (int i = 0; i < d; i++) {
        a[i] = T % 6;
        T /= 6;
    }
    std::reverse(a.begin(), a.end());
    
    int n = 50;
    std::cout << n << " " << n << "\n";
    std::vector<std::tuple<int, int, int, int>> e;
    
    e.emplace_back(0, 1, 1, 1);
    e.emplace_back(1, 0, 1, 1);
    for (int i = 0; i < 24; i++) {
        if (i < 23) {
            e.emplace_back(2 * i + 3, 2 * i + 1, 2 * i + 4, 2 * i + 1);
            e.emplace_back(2 * i + 3, 2 * i + 2, 2 * i + 4, 2 * i + 2);
            e.emplace_back(2 * i + 1, 2 * i + 3, 2 * i + 1, 2 * i + 4);
            e.emplace_back(2 * i + 2, 2 * i + 3, 2 * i + 2, 2 * i + 4);
        }
        if (i > 0) {
            e.emplace_back(2 * i + 3, 2 * i - 1, 2 * i + 3, 2 * i);
            e.emplace_back(2 * i - 1, 2 * i + 3, 2 * i, 2 * i + 3);
        }
        if (0 < i && i < 23) {
            e.emplace_back(2 * i + 4, 2 * i - 1, 2 * i + 4, 2 * i);
            e.emplace_back(2 * i - 1, 2 * i + 4, 2 * i, 2 * i + 4);
        }
        e.emplace_back(2 * i, 2 * i + 2, 2 * i + 1, 2 * i + 2);
        if (a[i] < 3) {
            e.emplace_back(2 * i + 2, 2 * i, 2 * i + 2, 2 * i + 1);
        }
        if (a[i] % 3 <= 1) {
            e.emplace_back(2 * i, 2 * i + 3, 2 * i + 1, 2 * i + 3);
        }
        if (a[i] % 3 <= 0) {
            e.emplace_back(2 * i + 3, 2 * i, 2 * i + 3, 2 * i + 1);
        }
    }
    
    std::cout << e.size() << "\n";
    for (auto [a, b, c, d] : e) {
        std::cout << a + 1 << " " << b + 1 << " " << c + 1 << " " << d + 1 << "\n";
    }
    
    return 0;
}
