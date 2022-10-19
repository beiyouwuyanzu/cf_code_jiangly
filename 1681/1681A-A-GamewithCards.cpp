// url:https://codeforces.com/contest/1681/problem/A
// time:2022-05-23 17:40:39
// name:A-GamewithCards

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int m;
    std::cin >> m;
    
    std::vector<int> b(m);
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
    }
    
    int x = *std::max_element(a.begin(), a.end());
    int y = *std::max_element(b.begin(), b.end());
    
    if (x >= y) {
        std::cout << "Alice\n";
    } else {
        std::cout << "Bob\n";
    }
    
    if (x > y) {
        std::cout << "Alice\n";
    } else {
        std::cout << "Bob\n";
    }
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
