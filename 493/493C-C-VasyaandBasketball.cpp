// url:https://codeforces.com/contest/493/problem/C
// time:2021-06-21 19:35:31
// name:C-VasyaandBasketball

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        a.emplace_back(x, 1);
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; i++) {
        int x;
        std::cin >> x;
        a.emplace_back(x, -1);
    }
    std::sort(a.begin(), a.end());
    int dif = 3 * (n - m), A = 3 * n;
    int curd = 3 * (n - m), cura = 3 * n;
    for (int l = 0, r; l < n + m; l = r) {
        r = l;
        while (r < n + m && a[l].first == a[r].first) {
            r++;
        }
        for (int i = l; i < r; i++) {
            curd -= a[i].second;
            cura -= std::max(0, a[i].second);
        }
        if (curd > dif || (curd == dif && cura > A)) {
            dif = curd;
            A = cura;
        }
    }
    std::cout << A << ":" << A - dif << "\n";
    return 0;
}
