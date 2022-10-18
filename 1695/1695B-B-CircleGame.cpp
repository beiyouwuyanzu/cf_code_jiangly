//url:https://codeforces.com/contest/1695/problem/B
//time:2022-06-18 17:53:28
//name:B-CircleGame

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    std::array<i64, 2> step{};
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    if (n % 2 == 1) {
        std::cout << "Mike\n";
        return;
    }
    
    for (int t = 0; t < 2; t++) {
        int min = std::numeric_limits<int>::max();
        int j = -1;
        for (int i = t; i < n; i += 2) {
            if (a[i] < min) {
                min = a[i];
                j = i / 2;
            }
        }
        step[t] = 1LL * (n / 2) * min + j;
    }
    
    if (n % 2 == 1 || step[0] > step[1]) {
        std::cout << "Mike\n";
    } else {
        std::cout << "Joe\n";
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

