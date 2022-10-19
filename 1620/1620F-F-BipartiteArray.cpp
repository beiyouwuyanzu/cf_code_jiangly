// url:https://codeforces.com/contest/1620/problem/F
// time:2021-12-18 19:52:41
// name:F-BipartiteArray

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> p(n);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
    }
    
    auto work = [&](auto p) {
        std::vector<int> g(n);
        for (int i = 0, j = 1E9; i < n; i++) {
            if (p[i] < j) {
                j = p[i];
                g[i]++;
            }
        }
        
        std::vector<int> q, Q;
        int ans = -1, L = -1E9, R = 1E9;
        bool nice = true;
        for (int i = 0; i < n; i++) {
            while (!q.empty() && p[i] < p[q.back()]) {
                nice &= (--g[q.back()] != 0);
                q.pop_back();
            }
            while (!Q.empty() && p[i] > p[Q.back()]) {
                nice &= (--g[Q.back()] != 0);
                Q.pop_back();
            }
            if (!nice) {
                break;
            }
            ans = i;
            L = q.empty() ? -1E9 : p[q.back()];
            R = Q.empty() ? 1E9 : p[Q.back()];
            if (g[i] == 0) {
                q.push_back(i);
                Q.push_back(i);
                g[i] += 2;
            }
        }
        return std::tuple(ans, L, R);
    };
    
    auto [f, lf, rf] = work(p);
    auto [g, lg, rg] = work(std::vector(p.rbegin(), p.rend()));
    
    if (f + g < n - 2 || (f + g == n - 2 && std::max(lf, lg) > std::min(rf, rg))) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
        std::vector<bool> neg(n);
        for (int i = 0, j = 1E9; i < f; i++) {
            if (p[i] <= j) {
                j = p[i];
                neg[i] = true;
            }
        }
        bool special = f + g == n - 2;
        int v = std::max(lf, lg);
        for (int i = f + 1, j = special ? v : p[f]; i < n; i++) {
            if (p[i] <= j) {
                j = p[i];
                neg[i] = true;
            }
        }
        for (int i = special ? f : f - 1, j = special ? v : p[f]; i >= 0; i--) {
            if (p[i] >= j) {
                j = p[i];
                neg[i] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            if (neg[i]) {
                p[i] = -p[i];
            }
            std::cout << p[i] << " \n"[i == n - 1];
        }
    }
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

