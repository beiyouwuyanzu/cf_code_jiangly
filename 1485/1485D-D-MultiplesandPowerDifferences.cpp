// url:https://codeforces.com/contest/1485/problem/D
// time:2021-02-12 18:09:59
// name:D-MultiplesandPowerDifferences

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x;
            std::cin >> x;
            if ((i + j) % 2 == 0) {
                std::cout << 720720;
            } else {
                std::cout << 720720 - x * x * x * x;
            }
            std::cout << " \n"[j == m - 1];
        }
    }
    return 0;
}
