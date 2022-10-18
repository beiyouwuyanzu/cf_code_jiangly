//url:https://codeforces.com/contest/1693/problem/A
//time:2022-06-16 17:40:28
//name:A-DirectionalIncrease

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    if (a == std::vector(n, 0)) {
        std::cout << "Yes\n";
        return;
    }
    
    int k = n - 1;
    while (a[k] == 0) {
        k--;
    }
    
    i64 s = 0;
    for (int i = 0; i < k; i++) {
        s += a[i];
        if (s <= 0) {
            std::cout << "No\n";
            return;
        }
    }
    s += a[k];
    if (s != 0) {
        std::cout << "No\n";
    } else {
        std::cout << "Yes\n";
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

