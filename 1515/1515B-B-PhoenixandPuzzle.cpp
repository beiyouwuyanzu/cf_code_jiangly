// url:https://codeforces.com/contest/1515/problem/B
// time:2021-05-02 17:40:44
// name:B-PhoenixandPuzzle

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
bool issquare(int n) {
    int x = std::sqrt(n);
    return x * x == n;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        if ((n % 4 == 0 && issquare(n / 4)) || (n % 2 == 0 && issquare(n / 2))) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
