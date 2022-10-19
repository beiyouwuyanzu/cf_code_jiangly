// url:https://codeforces.com/contest/495/problem/B
// time:2021-06-21 19:16:43
// name:B-ModularEquations

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int a, b;
    std::cin >> a >> b;
    if (a == b) {
        std::cout << "infinity\n";
        return 0;
    }
    if (a < b) {
        std::cout << "0\n";
        return 0;
    }
    int n = a - b;
    int ans = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i > b) {
                ans++;
            }
            if (i * i != n && n / i > b) {
                ans++;
            }
        }
    }
    std::cout << ans << "\n";
    return 0;
}
