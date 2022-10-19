// url:https://codeforces.com/contest/1676/problem/B
// time:2022-05-10 17:47:46
// name:B-EqualCandies

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::cout << std::accumulate(a.begin(), a.end(), 0) - n * *std::min_element(a.begin(), a.end()) << "\n";
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
