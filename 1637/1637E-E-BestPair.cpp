// url:https://codeforces.com/contest/1637/problem/E
// time:2022-02-12 17:58:21
// name:E-BestPair

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    
    std::map<int, int> cnt;
    
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        cnt[x]++;
    }
    
    std::set<std::pair<int, int>> bad;
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        bad.emplace(x, y);
    }
    
    std::vector<std::vector<int>> v(n + 1);
    std::vector<int> a;
    for (auto [x, c] : cnt) {
        if (v[c].empty()) {
            a.push_back(c);
        }
        v[c].push_back(x);
    }
    
    for (auto &a : v) {
        std::reverse(a.begin(), a.end());
    }
    
    i64 ans = 0;
    for (auto i : a) {
        for (auto j : a) {
            if (i == j) {
                for (auto x : v[i]) {
                    for (auto y : v[i]) {
                        if (x == y) {
                            break;
                        }
                        if (!bad.count(std::minmax(x, y))) {
                            ans = std::max(ans, 1LL * (i + i) * (x + y));
                            break;
                        }
                    }
                }
                
                break;
            }
            for (auto x : v[i]) {
                for (auto y : v[j]) {
                    if (!bad.count(std::minmax(x, y))) {
                        ans = std::max(ans, 1LL * (i + j) * (x + y));
                        break;
                    }
                }
                if (!bad.count(std::minmax(x, v[j][0]))) {
                    break;
                }
            }
        }
    }
    
    std::cout << ans << "\n";
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
