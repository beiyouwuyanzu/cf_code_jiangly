// url:https://codeforces.com/contest/1674/problem/F
// time:2022-05-02 17:58:26
// name:F-DesktopRearrangement

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, q;
    std::cin >> n >> m >> q;
    
    int o = 0, cnt = 0;
    
    std::vector<int> a(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            std::cin >> c;
            if (c == '*') {
                if (a[cnt]) {
                    o++;
                }
                cnt++;
                a[j * n + i] = 1;
                if (j * n + i < cnt) {
                    o++;
                }
            }
        }
    }
    
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        x--;
        y--;
        int i = y * n + x;
        
        if (!a[i]) {
            if (a[cnt]) {
                o++;
            }
            cnt++;
            a[i] = 1;
            if (i < cnt) {
                o++;
            }
        } else {
            if (i < cnt) {
                o--;
            }
            a[i] = 0;
            cnt--;
            if (a[cnt]) {
                o--;
            }
        }
        std::cout << cnt - o << "\n";
    }
    
    return 0;
}
