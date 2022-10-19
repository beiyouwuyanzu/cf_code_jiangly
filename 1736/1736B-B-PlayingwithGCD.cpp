// url:https://codeforces.com/contest/1736/problem/B
// time:2022-10-10 18:41:22
// name:B-PlayingwithGCD

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n + 1);
    for (auto &i : a) {
        std::cin >> i;
    }
    b[0] = a[0], b[n] = a[n - 1];
    for (int i = 1; i < n; i++) {
        b[i] = std::lcm(a[i - 1], a[i]);
    }
    for (int i = 0; i < n; i++) {
        if (std::gcd(b[i], b[i + 1]) != a[i]) {
            std::cout << "NO\n";
            return;
        }
    }
    std::cout << "YES\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

