// url:https://codeforces.com/contest/1539/problem/D
// time:2021-06-20 13:31:44
// name:D-PriceFixed

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::pair<i64, i64>> item(n);
    for (int i = 0; i < n; i++) {
        std::cin >> item[i].second >> item[i].first;
    }
    std::sort(item.begin(), item.end());
    i64 res = item[n - 1].second;
    i64 cur = 0;
    i64 ans = 0;
    for (int i = 0, j = n - 1; i <= j; i++) {
        while (i <= j && cur < item[i].first) {
            i64 t = std::min(res, item[i].first - cur);
            cur += t;
            ans += 2 * t;
            res -= t;
            if (res == 0) {
                j--;
                res = item[j].second;
            }
        }
        if (i > j) {
            break;
        }
        i64 t = i == j ? res : item[i].second;
        ans += t;
        cur += t;
    }
    std::cout << ans << "\n";
    return 0;
}
