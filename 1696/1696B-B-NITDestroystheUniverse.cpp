//url:https://codeforces.com/contest/1696/problem/B
//time:2022-06-25 17:52:32
//name:B-NITDestroystheUniverse

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
        std::cout << "0\n";
        return;
    }
    
    int l = 0, r = n - 1;
    while (a[l] == 0) {
        l++;
    }
    while (a[r] == 0) {
        r--;
    }
    
    if (std::count(a.begin() + l, a.begin() + r + 1, 0) == 0) {
        std::cout << "1\n";
    } else {
        std::cout << "2\n";
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

