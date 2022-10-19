// url:https://codeforces.com/contest/378/problem/B
// time:2021-06-19 22:56:54
// name:B-Semifinals

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a;
    std::vector ans(2, std::string(n, '0'));
    for (int i = 0; i < n / 2; i++) {
        ans[0][i] = ans[1][i] = '1';
    }
    for (int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        a.emplace_back(x, i);
        a.emplace_back(y, n + i);
    }
    std::sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        int j = a[i].second;
        ans[j / n][j % n] = '1';
    }
    std::cout << ans[0] << "\n";
    std::cout << ans[1] << "\n";
    return 0;
}
