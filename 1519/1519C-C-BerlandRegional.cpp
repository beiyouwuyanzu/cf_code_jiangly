//url:https://codeforces.com/contest/1519/problem/C
//time:2022-06-27 11:32:33
//name:C-BerlandRegional

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<i64> ans(n + 1);
    
    std::vector<std::vector<int>> a(n);
    std::vector<int> u(n);
    for (int i = 0; i < n; i++) {
        std::cin >> u[i];
        u[i]--;
    }
    
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        a[u[i]].push_back(x);
    }
    
    for (int x = 0; x < n; x++) {
        std::sort(a[x].begin(), a[x].end(), std::greater());
        
        int m = a[x].size();
        std::vector<i64> s(m + 1);
        for (int i = 0; i < m; i++) {
            s[i + 1] = s[i] + a[x][i];
        }
        
        for (int k = 1; k <= m; k++) {
            ans[k] += s[m - m % k];
        }
    }
    
    for (int k = 1; k <= n; k++) {
        std::cout << ans[k] << " \n"[k == n];
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

