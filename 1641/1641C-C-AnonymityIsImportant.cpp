// url:https://codeforces.com/contest/1641/problem/C
// time:2022-02-23 13:34:34
// name:C-AnonymityIsImportant

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::set<int> cand;
    for (int i = -1; i <= n; i++) {
        cand.insert(i);
    }
    
    std::map<int, int> s;
    
    while (q--) {
        int t;
        std::cin >> t;
        
        if (t == 0) {
            int l, r, x;
            std::cin >> l >> r >> x;
            l--;
            if (x == 0) {
                auto it = cand.lower_bound(l);
                while (*it < r) {
                    it = cand.erase(it);
                }
            } else {
                auto it = s.lower_bound(l);
                if (it != s.end() && it->second <= r) {
                    continue;
                }
                s[l] = r;
                it = s.find(l);
                while (it != s.begin() && r <= std::prev(it)->second) {
                    s.erase(std::prev(it));
                }
            }
        } else {
            int j;
            std::cin >> j;
            j--;
            if (!cand.count(j)) {
                std::cout << "NO\n";
            } else {
                int l = *std::prev(cand.find(j));
                int r = *std::next(cand.find(j));
                auto it = s.upper_bound(l);
                if (it != s.end() && it->second <= r) {
                    std::cout << "YES\n";
                } else {
                    std::cout << "N/A\n";
                }
            }
        }
    }
    
    return 0;
}
