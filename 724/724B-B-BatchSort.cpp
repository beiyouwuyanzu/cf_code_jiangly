// url:https://codeforces.com/contest/724/problem/B
// time:2021-12-22 11:10:21
// name:B-BatchSort

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
            a[i][j]--;
        }
    }
    
    for (int c1 = 0; c1 < m; c1++) {
        for (int c2 = c1; c2 < m; c2++) {
            bool nice = true;
            
            for (int i = 0; i < n; i++) {
                bool ok = false;
                for (int j1 = 0; j1 < m; j1++) {
                    for (int j2 = j1; j2 < m; j2++) {
                        auto v = a[i];
                        std::swap(v[j1], v[j2]);
                        std::swap(v[c1], v[c2]);
                        
                        if (std::is_sorted(v.begin(), v.end())) {
                            ok = true;
                        }
                        
                        v = a[i];
                        std::swap(v[c1], v[c2]);
                        std::swap(v[j1], v[j2]);
                        
                        if (std::is_sorted(v.begin(), v.end())) {
                            ok = true;
                        }
                    }
                }
                
                if (!ok) {
                    nice = false;
                }
            }
            
            if (nice) {
                std::cout << "YES\n";
                return 0;
            }
        }
    }
    
    std::cout << "NO\n";
    
    return 0;
}
