//url:https://codeforces.com/contest/1085/problem/C
//time:2021-07-15 11:26:51
//name:C-ConnectThree

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::pair<int, int> a[3];
    for (int i = 0; i < 3; i++) {
        std::cin >> a[i].first >> a[i].second;
    }
    
    std::set<std::pair<int, int>> s;
    
    std::sort(a, a + 3);
    
    for (auto i : {0, 2}) {
        auto [xl, xr] = std::minmax(a[1].first, a[i].first);
        auto [yl, yr] = std::minmax(a[1].second, a[i].second);
        for (int x = xl; x <= xr; x++) {
            s.emplace(x, a[i].second);
        }
        for (int y = yl; y <= yr; y++) {
            s.emplace(a[1].first, y);
        }
    }
    
    std::cout << s.size() << "\n";
    for (auto [x, y] : s) {
        std::cout << x << " " << y << "\n";
    }
    
    return 0;
}
