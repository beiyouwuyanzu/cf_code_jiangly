// url:https://codeforces.com/contest/1530/problem/D
// time:2021-07-17 17:56:10
// name:D-SecretSanta

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        
        int ans = 0;
        std::vector<int> a(n), b(n, -1), c(n, -1);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
            a[i]--;
            if (c[a[i]] < 0) {
                b[i] = a[i];
                c[a[i]] = i;
                ans++;
            }
        }
        
        std::vector<int> u, v;
        for (int i = 0; i < n; i++) {
            if (c[i] >= 0) {
                continue;
            }
            int j = i;
            while (b[j] >= 0) {
                j = b[j];
            }
            u.push_back(i);
            v.push_back(j);
        }
        
        if (!u.empty()) {
            if (u.size() > 1 || u[0] != v[0]) {
                for (int i = 0; i < int(u.size()); i++) {
                    b[v[i]] = u[(i + 1) % u.size()];
                }
            } else {
                int x = u[0];
                int y = a[x];
                b[x] = y;
                b[c[y]] = x;
            }
        }
        
        std::cout << ans << "\n";
        for (int i = 0; i < n; i++) {
            std::cout << b[i] + 1 << " \n"[i == n - 1];
        }
    }
    
    return 0;
}
