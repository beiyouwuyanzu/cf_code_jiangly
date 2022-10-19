// url:https://codeforces.com/contest/1624/problem/A
// time:2022-01-10 17:36:42
// name:A-PlusOneontheSubset

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::cout << *std::max_element(a.begin(), a.end()) - *std::min_element(a.begin(), a.end()) << "\n";
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

