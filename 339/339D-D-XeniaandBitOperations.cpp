// url:https://codeforces.com/contest/339/problem/D
// time:2023-04-28 19:57:20
// name:D-XeniaandBitOperations

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<int> a(2 << n);
    for (int i = 0; i < (1 << n); i++) {
        std::cin >> a[1 << n | i];
    }
    
    for (int i = (1 << n) - 1; i; i--) {
        if ((n - std::__lg(i)) % 2) {
            a[i] = a[2 * i] | a[2 * i + 1];
        } else {
            a[i] = a[2 * i] ^ a[2 * i + 1];
        }
    }
    
    while (m--) {
        int p, b;
        std::cin >> p >> b;
        p--;
        p += 1 << n;
        a[p] = b;
        while (p /= 2) {
            if ((n - std::__lg(p)) % 2) {
                a[p] = a[2 * p] | a[2 * p + 1];
            } else {
                a[p] = a[2 * p] ^ a[2 * p + 1];
            }
        }
        std::cout << a[1] << "\n";
    }
    
    return 0;
}
