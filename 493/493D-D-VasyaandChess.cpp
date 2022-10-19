// url:https://codeforces.com/contest/493/problem/D
// time:2021-06-21 20:06:43
// name:D-VasyaandChess

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    if (n % 2 == 0) {
        std::cout << "white\n";
        std::cout << "1 2\n";
    } else {
        std::cout << "black\n";
    }
    return 0;
}
