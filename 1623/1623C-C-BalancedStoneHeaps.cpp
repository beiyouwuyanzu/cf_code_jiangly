//url:https://codeforces.com/contest/1623/problem/C
//time:2021-12-28 17:36:22
//name:C-BalancedStoneHeaps

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<i64> h(n);
    for (int i = 0; i < n; i++) {
        std::cin >> h[i];
    }
    
    int l = 0, r = 1E9;
    
    while (l < r) {
        int x = (l + r + 1) / 2;
        
        auto a = h;
        for (int i = n - 1; i >= 2; i--) {
            if (a[i] < x) {
                break;
            }
            
            int d = std::min(h[i], a[i] - x) / 3;
            a[i] -= 3 * d;
            a[i - 1] += d;
            a[i - 2] += 2 * d;
        }
        
        if (*std::min_element(a.begin(), a.end()) < x) {
            r = x - 1;
        } else {
            l = x;
        }
    }
    std::cout << l << "\n";
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

