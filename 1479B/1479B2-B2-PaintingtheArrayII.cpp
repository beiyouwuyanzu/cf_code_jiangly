// url:https://codeforces.com/contest/1479/problem/B2
// time:2021-02-07 18:13:16
// name:B2-PaintingtheArrayII

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
    int mn = 0;
    std::set<int> mns{0};
    for (int i = 1; i <= n; i++) {
        int v = mn + + 1;
        if (mns.count(a[i])) {
            v--;
        }
        if (a[i] != a[i - 1]) {
            mn++;
        }
        if (v < mn) {
            mn = v;
            mns = {a[i - 1]};
        } else if (v == mn) {
            mns.insert(a[i - 1]);
        }
    }
    std::cout << mn << "\n";
    return 0;
}
