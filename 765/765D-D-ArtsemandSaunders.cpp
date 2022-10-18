//url:https://codeforces.com/contest/765/problem/D
//time:2021-07-12 15:00:15
//name:D-ArtsemandSaunders

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> f(n);
    for (int i = 0; i < n; i++) {
        std::cin >> f[i];
        f[i]--;
    }
    
    for (int i = 0; i < n; i++) {
        if (f[f[i]] != f[i]) {
            std::cout << "-1\n";
            return 0;
        }
    }
    
    std::vector<int> g(n), h;
    for (int i = 0; i < n; i++) {
        if (f[i] == i) {
            g[i] = h.size();
            h.push_back(i);
        }
    }
    
    for (int i = 0; i < n; i++) {
        g[i] = g[f[i]];
    }
    
    std::cout << h.size() << "\n";
    for (int i = 0; i < n; i++) {
        std::cout << g[i] + 1 << " \n"[i == n - 1];
    }
    for (int i = 0; i < int(h.size()); i++) {
        std::cout << h[i] + 1 << " \n"[i == int(h.size()) - 1];
    }
    
    return 0;
}
