//url:https://codeforces.com/contest/1700/problem/C
//time:2022-06-19 12:15:41
//name:C-HelpingtheNature

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    i64 ans = 0;
    i64 a0 = a[0];
    for (int i = 0; i < n - 1; i++) {
        int b = a[i + 1] - a[i];
        ans += std::abs(b);
        if (b < 0) {
            a0 += b;
        }
    }
    ans += std::abs(a0);
    
    std::cout << ans << "\n";
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

