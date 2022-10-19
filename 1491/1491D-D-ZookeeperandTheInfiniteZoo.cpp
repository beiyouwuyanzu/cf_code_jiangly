// url:https://codeforces.com/contest/1491/problem/D
// time:2021-02-28 17:04:47
// name:D-ZookeeperandTheInfiniteZoo

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
void solve() {
    int u, v;
    std::cin >> u >> v;
    if (u == v) {
        std::cout << "YES\n";
        return;
    }
    int l = 0, r = 29;
    while ((u >> l & 1) == (v >> l & 1)) {
        l++;
    }
    while ((u >> r & 1) == (v >> r & 1)) {
        r--;
    }
    if ((v >> l & 1) || (u >> r & 1)) {
        std::cout << "NO\n";
        return;
    }
    std::vector<int> a, b;
    for (int i = l; i <= r; i++) {
        if (u >> i & 1) {
            a.push_back(i);
        }
        if (v >> i & 1) {
            b.push_back(i);
        }
    }
    if (a.size() < b.size()) {
        std::cout << "NO\n";
        return;
    }
    for (int i = 0; i < int(b.size()); i++) {
        if (b[i] < a[i]) {
            std::cout << "NO\n";
            return;
        }
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

