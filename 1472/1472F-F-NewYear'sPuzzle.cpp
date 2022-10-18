//url:https://codeforces.com/contest/1472/problem/F
//time:2021-01-04 18:04:54
//name:F-NewYear'sPuzzle

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> a;
    for (int i = 0; i < m; i++) {
        int r, c;
        std::cin >> r >> c;
        r--;
        c--;
        a.emplace_back(c, r);
    }
    m += 2;
    std::sort(a.begin(), a.end());
    a.emplace_back(n, 0);
    a.emplace_back(n, 1);
    int x = 0, k = -1;
    for (int i = 0; i < m; ) {
        int nx = a[i].first;
        if ((a[i].second + nx) % 2 == k || (i + 1 < m && a[i + 1].first == nx && k != -1)) {
            std::cout << "NO\n";
            return;
        }
        if (i + 1 < m && a[i + 1].first == nx) {
            i += 2;
        } else if (k == -1) {
            k = (a[i].second + nx) % 2;
            i++;
        } else {
            k = -1;
            i++;
        }
        x = nx + 1;
    }
    std::cout << "YES\n";
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
