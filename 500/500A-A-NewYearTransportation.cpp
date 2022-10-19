// url:https://codeforces.com/contest/500/problem/A
// time:2021-06-22 11:14:44
// name:A-NewYearTransportation

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, t;
    std::cin >> n >> t;
    t--;
    std::vector<int> a(n - 1);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> a[i];
    }
    int u = 0;
    while (u < t) {
        u += a[u];
    }
    std::cout << (u == t ? "YES" : "NO") << "\n";
    return 0;
}
