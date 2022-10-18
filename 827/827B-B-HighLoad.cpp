//url:https://codeforces.com/contest/827/problem/B
//time:2021-03-31 15:46:11
//name:B-HighLoad

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    int d = (n - 1) / k;
    int r = n - k * d;
    std::cout << 2 * d + std::min(r - 1, 2) << "\n";
    for (int i = 1; i < n; i++) {
        if (i < r) {
            std::cout << "1 " << i + 1 << "\n";
        } else {
            std::cout << std::max(0, i - k) + 1 << " " << i + 1 << "\n";
        }
    }
    return 0;
}

