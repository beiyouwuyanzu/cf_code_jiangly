// url:https://codeforces.com/contest/1817/problem/A
// time:2023-04-29 17:45:15
// name:A-AlmostIncreasingSubsequence

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> s(n), f(n);
    for (int i = 1; i < n; i++) {
        s[i] = s[i - 1] + (a[i] > a[i - 1]);
        f[i] = f[i - 1] + (i >= 2 && a[i - 1] > a[i - 2] && a[i - 1] >= a[i]);
    }
    
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        l--, r--;
        
        int ans = 1 + f[r] - f[l] + s[r] - s[l];
        if (l < r && s[l] >= s[l + 1] && (l == 0 || s[l] <= s[l - 1])) {
            ans++;
        }
        std::cout << ans << "\n";
    }
    
    return 0;
}
