//url:https://codeforces.com/contest/1726/problem/B
//time:2022-09-06 17:40:47
//name:B-MainakandInterestingSequence

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    if (n > m) {
        std::cout << "No\n";
        return;
    }
    
    if (n % 2 == 0 && m % 2 != 0) {
        std::cout << "No\n";
        return;
    }
    
    std::vector<int> a(n, 1);
    if (n % 2 == 0) {
        a[n - 2] += (m - n) / 2;
        a[n - 1] += (m - n) / 2;
    } else {
        a[n - 1] += m - n;
    }
    
    std::cout << "Yes\n";
    for (int i = 0; i < n; i++) {
        std::cout << a[i] << " \n"[i == n - 1];
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
