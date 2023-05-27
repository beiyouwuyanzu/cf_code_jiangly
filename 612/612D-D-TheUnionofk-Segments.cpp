// url:https://codeforces.com/contest/612/problem/D
// time:2023-04-24 10:47:59
// name:D-TheUnionofk-Segments

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    std::vector<std::pair<int, int>> a;
    for (int i = 0; i < n; i++) {
        int l, r;
        std::cin >> l >> r;
        a.emplace_back(2 * l, 1);
        a.emplace_back(2 * r + 1, -1);
    }
    std::sort(a.begin(), a.end());
    
    int lst = 0, v = 0;
    std::vector<std::pair<int, int>> ans;
    for (auto [x, t] : a) {
        if (x > lst && v >= k) {
            if (!ans.empty() && ans.back().second == lst) {
                ans.back().second = x;
            } else {
                ans.emplace_back(lst, x);
            }
        }
        v += t;
        lst = x;
    }
    
    std::cout << ans.size() << "\n";
    for (auto [l, r] : ans) {
        std::cout << l / 2 << " " << (r-1) / 2 << "\n";
    }
    
    return 0;
}
