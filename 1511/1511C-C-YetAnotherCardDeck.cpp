// url:https://codeforces.com/contest/1511/problem/C
// time:2022-06-27 16:35:15
// name:C-YetAnotherCardDeck

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::array<int, 50> c;
    c.fill(n);
    
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        x--;
        c[x] = std::min(c[x], i);
    }
    
    for (int i = 0; i < q; i++) {
        int x;
        std::cin >> x;
        x--;
        
        std::cout << c[x] + 1 << " \n"[i == q - 1];
        for (int j = 0; j < 50; j++) {
            if (c[j] < c[x]) {
                c[j]++;
            }
        }
        c[x] = 0;
    }
    
    return 0;
}
