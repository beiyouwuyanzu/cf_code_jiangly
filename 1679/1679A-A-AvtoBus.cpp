// url:https://codeforces.com/contest/1679/problem/A
// time:2022-05-16 15:08:57
// name:A-AvtoBus

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    i64 n;
    std::cin >> n;
    
    if (n % 2 == 1 || n < 4) {
        std::cout << "-1\n";
        return;
    }
    
    std::cout << (n + 5) / 6 << " " << n / 4 << "\n";
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
