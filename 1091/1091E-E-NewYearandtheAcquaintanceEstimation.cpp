//url:https://codeforces.com/contest/1091/problem/E
//time:2021-07-15 22:16:52
//name:E-NewYearandtheAcquaintanceEstimation

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a.begin(), a.end(), std::greater<>());
    
    int parity = std::accumulate(a.begin(), a.end(), 0LL) % 2;
    
    std::vector<i64> sum(n + 1);
    for (int i = 0; i < n; i++) {
        sum[i + 1] = sum[i] + a[i];
    }
    
    std::vector<i64> f(n + 1), g(n + 1);
    for (int i = 0, j = n; i <= n; i++) {
        if (j < i) {
            j = i;
        }
        while (j > i && a[j - 1] <= i) {
            j--;
        }
        f[i] = i64(i) * (i - 1) + sum[n] - sum[j] + i64(i) * (j - i) - sum[i];
        g[i] = i64(i + 1) * i + sum[n] - sum[j] + i64(i + 1) * (j - i) - sum[i];
    }
    
    std::vector<int> ans;
    
    std::vector<i64> suf(n + 1), pre(n + 1);
    suf[n] = g[n];
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = std::min(suf[i + 1], g[i]);
    }
    pre[0] = f[0];
    for (int i = 1; i <= n; i++) {
        pre[i] = std::min(pre[i], f[i] + i);
    }
    
    i64 mn = 0;
    
    for (int x = n - (n % 2 != parity), i = 0; x >= 0; x -= 2) {
        if (x <= i) {
            mn = std::min(mn, f[x]);
        }
        if (x + 1 <= i) {
            mn = std::min(mn, f[x + 1]);
        }
        while (i < n && a[i] > x) {
            i++;
            if (i >= x) {
                mn = std::min(mn, f[i]);
            }
        }
        
        if (suf[i] >= x && pre[std::min(i, x)] >= 0 && mn + x >= 0) {
            ans.push_back(x);
        }
    }
    
    std::reverse(ans.begin(), ans.end());
    
    if (ans.empty()) {
        std::cout << "-1\n";
    } else {
        for (int i = 0; i < int(ans.size()); i++) {
            std::cout << ans[i] << " \n"[i == int(ans.size()) - 1];
        }
    }
    
    return 0;
}
