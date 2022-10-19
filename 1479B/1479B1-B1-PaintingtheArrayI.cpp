// url:https://codeforces.com/contest/1479/problem/B1
// time:2021-02-07 18:07:44
// name:B1-PaintingtheArrayI

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int inf = 1e9;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
    }
    int mx = 0;
    std::set<int> mxs{0};
    for (int i = 1; i <= n; i++) {
        int v = mx + 1;
        if (mxs.size() == 1 && *mxs.begin() == a[i]) {
            v--;
        }
        if (a[i] != a[i - 1]) {
            mx++;
        }
        if (v > mx) {
            mx = v;
            mxs = {a[i - 1]};
        } else if (v == mx) {
            mxs.insert(a[i - 1]);
        }
    }
    std::cout << mx << "\n";
    return 0;
}
