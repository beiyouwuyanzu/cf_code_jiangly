//url:https://codeforces.com/contest/1574/problem/B
//time:2022-06-12 07:23:42
//name:B-CombinatoricsHomework

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int a[3], m;
    std::cin >> a[0] >> a[1] >> a[2] >> m;
    
    std::sort(a, a + 3);
    
    if (std::max(0, a[0] - 1) + std::max(0, a[1] - 1) + std::max(0, a[2] - 1) >= m &&
            a[0] + a[1] + m >= a[2] - 1) {
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

