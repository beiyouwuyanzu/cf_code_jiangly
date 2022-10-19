// url:https://codeforces.com/contest/1743/problem/B
// time:2022-10-17 17:47:02
// name:B-PermutationValue

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::cout << 1;
    for (int i = n; i > 1; i--) {
        std::cout << " " << i;
    }
    std::cout << "\n";
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
