//url:https://codeforces.com/contest/1606/problem/D
//time:2022-06-10 11:48:05
//name:D-Red-BlueMatrix

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector a(n, std::vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[i][j];
        }
    }
    
    std::vector pmin(a), pmax(a), smin(a), smax(a);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < m; j++) {
            pmin[i][j] = std::min(pmin[i][j], pmin[i][j - 1]);
            pmax[i][j] = std::max(pmax[i][j], pmax[i][j - 1]);
        }
        for (int j = m - 2; j >= 0; j--) {
            smin[i][j] = std::min(smin[i][j], smin[i][j + 1]);
            smax[i][j] = std::max(smax[i][j], smax[i][j + 1]);
        }
    }
    
    for (int k = 1; k < m; k++) {
        std::vector<int> r(n);
        std::iota(r.begin(), r.end(), 0);
        std::sort(r.begin(), r.end(), [&](int i, int j) {
            return pmin[i][k - 1] < pmin[j][k - 1];
        });
        
        std::vector<int> lmin(n), lmax(n), rmin(n), rmax(n);
        for (int i = 0; i < n; i++) {
            lmin[i] = pmin[r[i]][k - 1];
            lmax[i] = pmax[r[i]][k - 1];
            rmin[i] = smin[r[i]][k];
            rmax[i] = smax[r[i]][k];
        }
        for (int i = 1; i < n; i++) {
            lmax[i] = std::max(lmax[i], lmax[i - 1]);
            rmin[i] = std::min(rmin[i], rmin[i - 1]);
        }
        for (int i = n - 2; i >= 0; i--) {
            lmin[i] = std::min(lmin[i], lmin[i + 1]);
            rmax[i] = std::max(rmax[i], rmax[i + 1]);
        }
        for (int i = 1; i < n; i++) {
            if (lmax[i - 1] < lmin[i] && rmax[i] < rmin[i - 1]) {
                std::cout << "YES\n";
                for (int j = 0; j < n; j++) {
                    std::cout << "RB"[pmax[j][k - 1] <= lmax[i - 1]];
                }
                std::cout << " " << k << "\n";
                return;
            }
        }
    }
    
    std::cout << "NO\n";
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
