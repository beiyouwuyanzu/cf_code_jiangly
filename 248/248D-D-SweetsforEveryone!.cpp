// url:https://codeforces.com/contest/248/problem/D
// time:2023-04-23 20:41:00
// name:D-SweetsforEveryone!

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, t;
    std::cin >> n >> t;
    
    std::string s;
    std::cin >> s;
    
    int cntH = std::count(s.begin(), s.end(), 'H');
    
    int ri = n-1;
    while (s[ri] != 'H') {
        ri--;
    }
    
    if (t < ri+1) {
        std::cout << -1 << "\n";
        return 0;
    }
    
    std::vector<int> house, shop;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'H') {
            house.push_back(i);
        }
        if (s[i] == 'S') {
            shop.push_back(i);
        }
    }
    
    auto check = [&](int x) {
        if (x + shop.size() < house.size()) {
            return false;
        }
        int lst = -1;
        int ans = t+1;
        int res = 0;
        int rightmost = std::max(house.back(), shop[house.size()-1-x]);
        for (int i = x; i < house.size(); i++) {
            ans = std::min(ans, res + house[i]+1 + 2 * (rightmost - house[i]));
            if (house[i] < shop[i-x]) {
                res += 2 * (shop[i-x] - std::max(lst, house[i]));
                lst = shop[i-x];
            }
        }
        return ans <= t;
    };
    
    int lo = 0, hi = cntH;
    while (lo < hi) {
        int x = (lo + hi) / 2;
        if (check(x)) {
            hi = x;
        } else {
            lo = x+1;
        }
    }
    std::cout << lo << "\n";
    
    return 0;
}
