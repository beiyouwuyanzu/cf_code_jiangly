// url:https://codeforces.com/contest/612/problem/E
// time:2023-04-24 10:53:27
// name:E-SquareRootofPermutation

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
    }
    
    std::vector<std::vector<int>> f;
    std::vector<bool> vis(n);
    std::vector<int> q(n);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int j = i;
            std::vector<int> a;
            while (!vis[j]) {
                vis[j] = true;
                a.push_back(j);
                j = p[j];
            }
            if (a.size() % 2 == 1) {
                int t = (a.size() + 1) / 2;
                for (int j = 0; j < a.size(); j++) {
                    q[a[j]] = a[(j + t) % a.size()];
                }
            } else {
                f.push_back(a);
            }
        }
    }
    
    std::sort(f.begin(), f.end(), [&](auto a, auto b) {
        return a.size() < b.size();
    });
    
    if (f.size() % 2) {
        std::cout << -1 << "\n";
        return 0;
    }
    for (int i = 0; i < f.size(); i += 2) {
        if (f[i].size() != f[i+1].size()) {
            std::cout << -1 << "\n";
            return 0;
        }
        
        for (int j = 0; j < f[i].size(); j++) {
            q[f[i][j]] = f[i+1][j];
            q[f[i+1][j]] = f[i][(j+1) % f[i].size()];
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << q[i]+1 << " \n"[i == n-1];
    }
    
    return 0;
}
