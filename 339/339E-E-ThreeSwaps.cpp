// url:https://codeforces.com/contest/339/problem/E
// time:2023-04-28 20:33:52
// name:E-ThreeSwaps

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
    
    std::vector<int> goal(n);
    std::iota(goal.begin(), goal.end(), 0);
    
    std::vector<std::pair<int, int>> ans;
    std::function<void(int, std::vector<int>)> dfs = [&](int t, std::vector<int> p) {
        if (t == 3) {
            if (p == goal) {
                std::cout << ans.size() << "\n";
                std::reverse(ans.begin(), ans.end());
                for (auto [l, r] : ans) {
                    std::cout << l << " " << r << "\n";
                }
                std::exit(0);
            }
            return;
        }
        std::vector<int> invp(n);
        for (int i = 0; i < n; i++) {
            invp[p[i]] = i;
        }
        std::vector<int> e;
        int cnt = 0;
        for (int i = 0; i <= n; i++) {
            if (!i || i == n || std::abs(p[i] - p[i - 1]) != 1) {
                cnt++;
                e.push_back(i);
                if (i) {
                    e.push_back(i - 1);
                }
                if (i < n) {
                    e.push_back(i + 1);
                }
                for (auto j : {i - 1, i}) {
                    if (0 <= j && j < n) {
                        for (auto k : {p[j] - 1, p[j] + 1}) {
                            if (0 <= k && k < n) {
                                if (invp[k] < j) {
                                    e.push_back(invp[k]);
                                } else {
                                    e.push_back(invp[k] + 1);
                                }
                            }
                        }
                    }
                }
            }
        }
        if (cnt > (4 - t) * 2) {
            return;
        }
        std::sort(e.begin(), e.end());
        e.erase(std::unique(e.begin(), e.end()), e.end());
        int m = e.size();
        for (int l = 0; l < m; l++) {
            for (int r = l; r < m; r++) {
                auto q = p;
                if (e[l] + 1 < e[r]) {
                    std::reverse(q.begin() + e[l], q.begin() + e[r]);
                    ans.emplace_back(e[l] + 1, e[r]);
                }
                dfs(t + 1, q);
                if (e[l] + 1 < e[r]) {
                    ans.pop_back();
                }
            }
        }
    };
    dfs(0, p);
    
    return 0;
}
