// url:https://codeforces.com/contest/1638/problem/F
// time:2022-02-14 18:44:43
// name:F-TwoPosters

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<i64> h(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }
    
    i64 ans = 0;
    
    std::vector<i64> pre(n + 1), suf(n + 1);
    for (int i = 0; i < n; i++) {
        i64 mn = h[i];
        for (int j = i; j < n; j++) {
            mn = std::min(mn, h[j]);
            pre[j + 1] = std::max(pre[j + 1], (j - i + 1) * mn);
            suf[i] = std::max(suf[i], (j - i + 1) * mn);
        }
    }
    
    for (int i = 0; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            ans = std::max(ans, pre[i] + suf[j]);
        }
    }
    
    for (int i = 0; i < n; i++) {
        auto a = h;
        for (int j = i - 1; j >= 0; j--) {
            a[j] = std::min(a[j], a[j + 1]);
        }
        for (int j = i + 1; j < n; j++) {
            a[j] = std::min(a[j], a[j - 1]);
        }
        
        int l = i, r = i + 1;
        while (l > 0 && a[l - 1] == a[i]) {
            l--;
        }
        while (r < n && a[r] == a[i]) {
            r++;
        }
        
        std::vector<i64> c(n);
        std::merge(a.begin(), a.begin() + i, a.rbegin(), a.rbegin() + n - i, c.begin());
        
        int l1 = 0, r1 = n, l2 = l, r2 = r;
        for (auto x : c) {
            while (a[l1] < x) {
                l1++;
            }
            while (a[r1 - 1] < x) {
                r1--;
            }
            while (l2 > 0 && a[l2 - 1] >= a[i] - x) {
                l2--;
            }
            while (r2 < n && a[r2] >= a[i] - x) {
                r2++;
            }
            
            ans = std::max(ans, a[i] * (r - l) + std::max(x * (l - l1), (a[i] - x) * (l - l2)) + std::max(x * (r1 - r), (a[i] - x) * (r2 - r)));
        }
        
        i64 mx = 0;
        for (int j = l - 1, k = n; j >= 0; j--) {
            while (k > r && a[j] + a[k - 1] <= a[i]) {
                k--;
                mx = std::max(mx, (k + 1 - l) * a[k]);
            }
            ans = std::max(ans, mx + (r - j) * a[j]);
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
