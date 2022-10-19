// url:https://codeforces.com/contest/1646/problem/A
// time:2022-03-04 19:43:40
// name:A-SquareCounting

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    i64 s;
    std::cin >> n >> s;
    
    std::cout << s / n / n << "\n";
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
