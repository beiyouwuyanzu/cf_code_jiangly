// url:https://codeforces.com/contest/1806/problem/E
// time:2023-03-20 22:00:59
// name:E-TreeMaster

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<int> p(n, -1), dep(n);
    for (int i = 1; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
        dep[i] = dep[p[i]] + 1;
    }
    std::vector<std::vector<int>> v(n);
    std::vector<int> id(n);
    for (int i = 0; i < n; i++) {
        id[i] = v[dep[i]].size();
        v[dep[i]].push_back(i);
    }
    
    std::vector<std::vector<i64>> g(n);
    for (int i = 0; i < n; i++) {
        if (v[dep[i]].size() <= 300) {
            g[i].resize(v[dep[i]].size(), -1);
        }
    }
    
    std::function<i64(int, int)> f = [&](int x, int y) {
        if (x == -1) {
            return 0LL;
        }
        if (v[dep[x]].size() <= 300 && g[x][id[y]] != -1) {
            return g[x][id[y]];
        }
        i64 res = f(p[x], p[y]) + 1LL * a[x] * a[y];
        if (v[dep[x]].size() <= 300) {
            g[x][id[y]] = res;
        }
        return res;
    };
    
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        
        std::cout << f(x, y) << "\n";
    }
    
    return 0;
}
