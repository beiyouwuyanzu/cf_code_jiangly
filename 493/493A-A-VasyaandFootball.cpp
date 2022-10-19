// url:https://codeforces.com/contest/493/problem/A
// time:2021-06-21 19:26:43
// name:A-VasyaandFootball

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string home, away;
    std::cin >> home >> away;
    int n;
    std::cin >> n;
    std::vector<int> a(200);
    for (int i = 0; i < n; i++) {
        int t, m;
        char team, tp;
        std::cin >> t >> team >> m >> tp;
        int u = (team == 'a') * 100 + m;
        a[u] += (tp == 'y' ? 1 : 2);
        if (a[u] >= 2) {
            std::cout << (team == 'h' ? home : away) << " " << m << " " << t << "\n";
            a[u] = -1e9;
        }
    }
    return 0;
}
