// url:https://codeforces.com/contest/1674/problem/A
// time:2022-05-02 17:42:22
// name:A-NumberTransformation

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int x, y;
    std::cin >> x >> y;
    
    if (x == y) {
        std::cout << "1 1\n";
        return;
    }
    
    for (int b = 2; b * x <= y; b++) {
        int v = x;
        for (int a = 1; v <= y; a++) {
            v *= b;
            if (v == y) {
                std::cout << a << " " << b << "\n";
                return;
            }
        }
    }
    
    std::cout << "0 0\n";
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
