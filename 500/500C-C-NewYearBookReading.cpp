// url:https://codeforces.com/contest/500/problem/C
// time:2021-06-22 11:41:57
// name:C-NewYearBookReading

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> w(n);
    for (int i = 0; i < n; i++) {
        std::cin >> w[i];
    }
    std::vector<int> first(n, m);
    std::vector<int> b(m);
    int ans = 0;
    for (int i = 0; i < m; i++) {
        std::cin >> b[i];
        b[i]--;
    }
    for (int i = m - 1; i >= 0; i--) {
        first[b[i]] = i;
    }
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return first[i] < first[j];
    });
    for (int i = 0; i < m; i++) {
        int j = 0;
        while (p[j] != b[i]) {
            ans += w[p[j]];
            j++;
        }
        std::rotate(p.begin(), p.begin() + j, p.begin() + j + 1);
    }
    std::cout << ans << "\n";
    return 0;
}
