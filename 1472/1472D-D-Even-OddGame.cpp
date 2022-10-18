//url:https://codeforces.com/contest/1472/problem/D
//time:2021-01-04 17:42:59
//name:D-Even-OddGame

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        std::sort(a.begin(), a.end(), std::greater<>());
        i64 sum = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] % 2 == i % 2) {
                if (i % 2 == 0) {
                    sum += a[i];
                } else {
                    sum -= a[i];
                }
            }
        }
        if (sum > 0) {
            std::cout << "Alice\n";
        } else if (sum == 0) {
            std::cout << "Tie\n";
        } else {
            std::cout << "Bob\n";
        }
    }
    return 0;
}
