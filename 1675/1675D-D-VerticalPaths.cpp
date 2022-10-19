// url:https://codeforces.com/contest/1675/problem/D
// time:2022-05-05 17:44:16
// name:D-VerticalPaths

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> p(n);
    std::vector<bool> leaf(n, true);
    for (int i = 0; i < n; i++) {
        std::cin >> p[i];
        p[i]--;
        if (p[i] != i) {
            leaf[p[i]] = false;
        }
    }
    std::vector<bool> vis(n);
    
    std::cout << std::count(leaf.begin(), leaf.end(), true) << "\n";
    
    for (int i = 0; i < n; i++) {
        if (leaf[i]) {
            std::vector<int> a;
            for (int j = i; !vis[j]; j = p[j]) {
                vis[j] = true;
                a.push_back(j);
            }
            std::reverse(a.begin(), a.end());
            std::cout << a.size() << "\n";
            for (auto x : a) {
                std::cout << x + 1 << " \n"[x == a.back()];
            }
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
