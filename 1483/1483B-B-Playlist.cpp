//url:https://codeforces.com/contest/1483/problem/B
//time:2021-03-21 16:44:17
//name:B-Playlist

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        std::set<int> s, q;
        for (int i = 0; i < n; i++) {
            s.insert(i);
            q.insert(i);
        }
        int last = 0;
        std::vector<int> ans;
        while (!q.empty() && !s.empty()) {
            auto i = q.lower_bound(last);
            if (i == q.end()) {
                i = q.begin();
            }
            if (!s.count(*i)) {
                q.erase(i);
                continue;
            }
            auto j = s.upper_bound(*i);
            if (j == s.end()) {
                j = s.begin();
            }
            int x = *i;
            if (std::gcd(a[x], a[*j]) == 1) {
                last = *j + 1;
                ans.push_back(*j);
                s.erase(*j);
            } else {
                q.erase(i);
            }
        }
        std::cout << ans.size();
        for (auto i : ans) {
            std::cout << " " << i + 1;
        }
        std::cout << "\n";
    }
    return 0;
}

