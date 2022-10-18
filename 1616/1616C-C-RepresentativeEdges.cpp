//url:https://codeforces.com/contest/1616/problem/C
//time:2021-12-29 18:45:19
//name:C-RepresentativeEdges

#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int ans = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int res = 0;
            for (int k = 0; k < n; k++) {
                if ((i - k) * (a[j] - a[k]) - (j - k) * (a[i] - a[k]) == 0) {
                    res++;
                }
            }
            ans = std::max(ans, res);
        }
    }
    
    std::cout << n - ans << "\n";
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

