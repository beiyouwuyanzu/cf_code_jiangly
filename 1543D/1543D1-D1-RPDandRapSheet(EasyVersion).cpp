// url:https://codeforces.com/contest/1543/problem/D1
// time:2021-07-07 18:12:43
// name:D1-RPDandRapSheet(EasyVersion)

#include <bits/stdc++.h>

using i64 = long long;

int bitxor(int x, int y, int k) {
    int z = 0;
    for (int i = 1; i <= x || i <= y; i *= k) {
        z += (x / i + y / i) % k * i;
    }
    return z;
}

int bitxorinv(int x, int y, int k) {
    int z = 0;
    for (int i = 1; i <= x || i <= y; i *= k) {
        z += (x / i - y / i % k + k) % k * i;
    }
    return z;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    while (t--) {
        int n, k;
        std::cin >> n >> k;
        int cur = 0;
        for (int i = 0; i < n; i++) {
            int x = i;
            if (i % 2 == 0) {
                x = bitxor(cur, x, k);
            } else {
                x = bitxorinv(cur, x, k);
            }
            std::cout << x << std::endl;
            int r;
            std::cin >> r;
            if (r == 1) {
                break;
            }
            cur = bitxorinv(x, cur, k);
        }
    }
    
    return 0;
}
