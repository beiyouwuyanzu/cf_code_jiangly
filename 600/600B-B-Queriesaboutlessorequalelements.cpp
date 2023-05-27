// url:https://codeforces.com/contest/600/problem/B
// time:2023-04-24 06:27:45
// name:B-Queriesaboutlessorequalelements

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> a(n), b(m);
    for (auto &x : a) {
        std::cin >> x;
    }
    for (auto &x : b) {
        std::cin >> x;
    }
    
    std::sort(a.begin(), a.end());
    for (int i = 0; i < m; i++) {
        std::cout << std::upper_bound(a.begin(), a.end(), b[i]) - a.begin() << " \n"[i == m-1];
    }
    
    return 0;
}
