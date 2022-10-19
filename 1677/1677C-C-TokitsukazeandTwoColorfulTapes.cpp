// url:https://codeforces.com/contest/1677/problem/C
// time:2022-05-08 17:50:15
// name:C-TokitsukazeandTwoColorfulTapes

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n), p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        a[i]--;
    }
    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
        b[i]--;
        p[a[i]] = b[i];
    }
    
    i64 ans = 0;
    int x = 0;
    std::vector<bool> vis(n);
    for (int i = 0; i < n; i++) {
        if (vis[i]) {
            continue;
        }
        int len = 0;
        for (int j = i; !vis[j]; j = p[j]) {
            vis[j] = true;
            len++;
        }
        x += len / 2;
    }
    for (int i = 0; i < x; i++) {
        ans += n - 1 - i - i;
    }
    ans *= 2;
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
