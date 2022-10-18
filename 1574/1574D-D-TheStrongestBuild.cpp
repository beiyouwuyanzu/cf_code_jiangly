//url:https://codeforces.com/contest/1574/problem/D
//time:2022-06-12 07:38:40
//name:D-TheStrongestBuild

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        int c;
        std::cin >> c;
        a[i].resize(c);
        for (int j = 0; j < c; j++) {
            std::cin >> a[i][j];
        }
    }
    
    int m;
    std::cin >> m;
    
    std::set<std::vector<int>> banned;
    for (int i = 0; i < m; i++) {
        std::vector<int> b(n);
        for (int j = 0; j < n; j++) {
            std::cin >> b[j];
            b[j]--;
        }
        banned.insert(b);
    }
    
    std::vector<int> b(n);
    for (int i = 0; i < n; i++) {
        b[i] = a[i].size() - 1;
    }
    
    i64 ans = -1;
    if (!banned.contains(b)) {
        ans = 0;
        for (int i = 0; i < n; i++) {
            ans += a[i].back();
        }
    }
    
    for (auto c : banned) {
        i64 val = 0;
        for (int i = 0; i < n; i++) {
            val += a[i][c[i]];
        }
        for (int i = 0; i < n; i++) {
            if (c[i] > 0) {
                c[i]--;
                i64 res = val - a[i][c[i] + 1] + a[i][c[i]];
                if (!banned.contains(c) && res > ans) {
                    b = c;
                    ans = res;
                }
                c[i]++;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << b[i] + 1 << " \n"[i == n - 1];
    }
    
    return 0;
}

