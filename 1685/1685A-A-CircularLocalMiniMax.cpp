//url:https://codeforces.com/contest/1685/problem/A
//time:2022-05-25 20:40:44
//name:A-CircularLocalMiniMax

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a.begin(), a.end());
    
    if (n % 2 == 1) {
        std::cout << "NO\n";
        return;
    }
    
    for (int i = 0; i < n / 2; i++) {
        if (a[i] == a[i + n / 2]) {
            std::cout << "NO\n";
            return;
        }
        if (i + 1 < n / 2 && a[i + 1] == a[i + n / 2]) {
            std::cout << "NO\n";
            return;
        }
    }
    
    std::cout << "YES\n";
    for (int i = 0; i < n / 2; i++) {
        std::cout << a[i] << " " << a[i + n / 2] << " \n"[i == n / 2 - 1];
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
