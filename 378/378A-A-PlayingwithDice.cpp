// url:https://codeforces.com/contest/378/problem/A
// time:2021-06-19 22:58:59
// name:A-PlayingwithDice

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int a, b;
    std::cin >> a >> b;
    int ans[3] = {};
    for (int x = 1; x <= 6; x++) {
        int da = std::abs(a - x);
        int db = std::abs(b - x);
        if (da < db) {
            ans[0]++;
        } else if (da == db) {
            ans[1]++;
        } else {
            ans[2]++;
        }
    }
    for (int i = 0; i <= 2; i++) {
        std::cout << ans[i] << " \n"[i == 2];
    }
    return 0;
}
