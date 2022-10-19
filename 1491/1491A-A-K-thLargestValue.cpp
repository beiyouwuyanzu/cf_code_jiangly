// url:https://codeforces.com/contest/1491/problem/A
// time:2021-02-28 16:36:54
// name:A-K-thLargestValue

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        sum += a[i];
    }
    while (q--) {
        int t, x;
        std::cin >> t >> x;
        if (t == 1) {
            x--;
            sum -= a[x];
            a[x] = 1 - a[x];
            sum += a[x];
        } else {
            if (x <= sum) {
                std::cout << "1\n";
            } else {
                std::cout << "0\n";
            }
        }
    }
    return 0;
}

