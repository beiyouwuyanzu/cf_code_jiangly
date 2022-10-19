// url:https://codeforces.com/contest/734/problem/C
// time:2021-12-23 18:59:06
// name:C-AntonandMakingPotions

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m, k;
    std::cin >> n >> m >> k;
    
    int x, s;
    std::cin >> x >> s;
    
    m++;
    k++;
    std::vector<std::pair<int, int>> a(m), b(k);
    for (int i = 0; i < m - 1; i++) {
        std::cin >> a[i].first;
    }
    for (int i = 0; i < m - 1; i++) {
        std::cin >> a[i].second;
    }
    for (int i = 1; i < k; i++) {
        std::cin >> b[i].first;
    }
    for (int i = 1; i < k; i++) {
        std::cin >> b[i].second;
    }
    a[m - 1] = {x, 0};
    std::sort(a.begin(), a.end());
    
    for (int i = 1; i < m; i++) {
        a[i].second = std::min(a[i].second, a[i - 1].second);
    }
    
    i64 ans = 5E18;
    for (int i = 0, j = -1; i < m; i++) {
        while (j + 1 < k && b[j + 1].second <= s - a[i].second) {
            j++;
        }
        if (j != -1) {
            ans = std::min(ans, 1LL * a[i].first * (n - b[j].first));
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
