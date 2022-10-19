// url:https://codeforces.com/contest/1517/problem/C
// time:2021-04-23 17:52:19
// name:C-Fillomino2

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    std::vector<int> a(n);
    std::iota(a.begin(), a.end(), 0);
    std::vector<std::vector<int>> c(n, std::vector<int>(n));
    for (int t = 0; t < n; t++) {
        for (int i = 0; i < int(a.size()); i++) {
            c[t + i][i] = p[a[i]];
        }
        int x = -1;
        for (int i = 0; i < int(a.size()); i++) {
            if (p[a[i]] == t + 1) {
                x = i;
            }
        }
        a.erase(a.begin() + x);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            std::cout << c[i][j] << " \n"[j == i];
        }
    }
    return 0;
}
