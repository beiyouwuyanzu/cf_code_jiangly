// url:https://codeforces.com/contest/1520/problem/E
// time:2021-05-05 18:27:11
// name:E-ArrangingTheSheep

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
        std::string s;
        std::cin >> s;
        std::vector<int> a;
        int empty = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '.') {
                empty++;
            } else {
                a.push_back(empty);
            }
        }
        int mid = (a.size() - 1) / 2;
        i64 ans = 0;
        for (auto x : a) {
            ans += std::abs(x - a[mid]);
        }
        std::cout << ans << "\n";
    }
    return 0;
}
