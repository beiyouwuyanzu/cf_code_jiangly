//url:https://codeforces.com/contest/641/problem/C
//time:2021-07-09 21:31:26
//name:C-LittleArtemandDance

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    int p0 = 0, p1 = 1;
    for (int i = 0; i < q; i++) {
        int t;
        std::cin >> t;
        
        if (t == 1) {
            int x;
            std::cin >> x;
            p0 = (p0 + x + n) % n;
            p1 = (p1 + x + n) % n;
        } else {
            p0 ^= 1;
            p1 ^= 1;
        }
    }
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            a[(p0 + i) % n] = i;
        } else {
            a[(p1 + i - 1) % n] = i;
        }
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << a[i] + 1 << " \n"[i == n - 1];
    }
    
    return 0;
}
