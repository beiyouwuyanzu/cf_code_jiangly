// url:https://codeforces.com/contest/1515/problem/A
// time:2021-05-02 17:38:32
// name:A-PhoenixandGold

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
        int n, x;
        std::cin >> n >> x;
        std::vector<int> w(n);
        for (int i = 0; i < n; i++) {
            std::cin >> w[i];
        }
        std::sort(w.begin(), w.end());
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += w[i];
            if (sum == x && i < n - 1) {
                sum += w[i + 1] - w[i];
                std::swap(w[i], w[i + 1]);
            }
        }
        if (sum == x) {
            std::cout << "NO\n";
        } else {
            std::cout << "YES\n";
            for (int i = 0; i < n; i++) {
                std::cout << w[i] << " \n"[i == n - 1];
            }
        }
    }
    return 0;
}
