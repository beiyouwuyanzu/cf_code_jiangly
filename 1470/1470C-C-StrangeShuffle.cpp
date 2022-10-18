//url:https://codeforces.com/contest/1470/problem/C
//time:2021-01-05 18:02:59
//name:C-StrangeShuffle

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int query(int q) {
    std::cout << "? " << q + 1 << std::endl;
    int ans;
    std::cin >> ans;
    return ans;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    int B = std::sqrt(n) - 1;
    for (int i = 0; i < B; i++) {
        query(i);
    }
    int x = 0;
    int v = query(x);
    while (v == k) {
        x = (x + B) % n;
        v = query(x);
    }
    if (v < k) {
        while (query((x + B) % n) < k) {
            x = (x + B) % n;
        }
        while (query((x + 1) % n) < k) {
            x = (x + 1) % n;
        }
        x = (x + 1) % n;
    } else {
        while (query((x - B + n) % n) > k) {
            x = (x - B + n) % n;
        }
        while (query((x - 1 + n) % n) > k) {
            x = (x - 1 + n) % n;
        }
        x = (x - 1 + n) % n;
    }
    std::cout << "! " << x + 1 << "\n";
    return 0;
}
