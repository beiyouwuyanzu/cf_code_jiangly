// url:https://codeforces.com/contest/1479/problem/A
// time:2021-02-07 17:43:53
// name:A-SearchingLocalMinimum

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int query(int x) {
    std::cout << "? " << x + 1 << std::endl;
    std::cin >> x;
    return x - 1;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    int l = -1, r = n;
    while (r - l > 2) {
        int m1 = (l + r) / 2;
        int m2 = m1 + 1;
        if (query(m1) > query(m2)) {
            l = m1;
        } else {
            r = m2;
        }
    }
    std::cout << "! " << r << "\n";
    return 0;
}
