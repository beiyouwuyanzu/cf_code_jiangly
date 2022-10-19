// url:https://codeforces.com/contest/1670/problem/D
// time:2022-05-06 18:47:44
// name:D-VerySuspicious

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    int l = 1, r = 40000;
    while (l < r) {
        int m = (l + r) / 2;
        int a = m / 3;
        int b = (m - a) / 2;
        int c = m - a - b;
        if ((a * b + b * c + c * a) * 2 >= n) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    
    std::cout << l << "\n";
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
