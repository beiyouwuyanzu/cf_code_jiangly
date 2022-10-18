//url:https://codeforces.com/contest/1472/problem/A
//time:2021-01-04 17:36:39
//name:A-CardsforFriends

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
        int w, h, n;
        std::cin >> w >> h >> n;
        if ((w & -w) * (h & -h) >= n) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }
    }
    return 0;
}
