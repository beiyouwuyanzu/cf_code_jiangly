// url:https://codeforces.com/contest/1638/problem/B
// time:2022-02-14 18:46:33
// name:B-OddSwapSort

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> odd, even;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        
        if (x % 2 == 1) {
            odd.push_back(x);
        } else {
            even.push_back(x);
        }
    }
    
    if (std::is_sorted(odd.begin(), odd.end()) && std::is_sorted(even.begin(), even.end())) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
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
