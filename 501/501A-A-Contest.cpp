// url:https://codeforces.com/contest/501/problem/A
// time:2021-06-24 16:17:04
// name:A-Contest

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    int s1 = std::max(3 * a / 10, a - a / 250 * c);
    int s2 = std::max(3 * b / 10, b - b / 250 * d);
    if (s1 > s2) {
        std::cout << "Misha\n";
    } else if (s1 < s2) {
        std::cout << "Vasya\n";
    } else {
        std::cout << "Tie\n";
    }
    return 0;
}
