// url:https://codeforces.com/contest/1648/problem/A
// time:2022-03-06 12:58:00
// name:A-WeirdSum

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::map<int, std::vector<int>> sx, sy;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int c;
            std::cin >> c;
            sx[c].push_back(i);
            sy[c].push_back(j);
        }
    }
    
    auto solve = [&](auto s) {
        i64 ans = 0;
        for (auto [x, v] : s) {
            std::sort(v.begin(), v.end());
            i64 s = 0, c = 0;
            for (auto i : v) {
                ans += i * c - s;
                s += i;
                c++;
            }
        }
        return ans;
    };
    
    auto ans = solve(sx) + solve(sy);
    
    std::cout << ans << "\n";
    
    return 0;
}
