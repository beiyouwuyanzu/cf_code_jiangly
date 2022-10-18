//url:https://codeforces.com/contest/1622/problem/A
//time:2022-06-09 15:42:13
//name:A-ConstructaRectangle

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::array<int, 3> l;
    for (int i = 0; i < 3; i++) {
        std::cin >> l[i];
    }
    
    std::sort(l.begin(), l.end());
    
    if (l[0] + l[1] == l[2] || (l[0] % 2 == 0 && l[1] == l[2]) || (l[2] % 2 == 0 && l[0] == l[1])) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
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
