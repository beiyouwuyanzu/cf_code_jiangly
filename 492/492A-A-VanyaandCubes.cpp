// url:https://codeforces.com/contest/492/problem/A
// time:2021-06-24 18:47:49
// name:A-VanyaandCubes

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    int d = 0;
    int s = 0;
    while (s + (d + 1) * (d + 2) / 2 <= n) {
        d++;
        s += d * (d + 1) / 2;
    }
    std::cout << d << "\n";
    return 0;
}
