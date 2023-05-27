// url:https://codeforces.com/contest/282/problem/B
// time:2023-04-27 08:50:38
// name:B-PaintingEggs

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> a(n), b(n);
    int s = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> a[i] >> b[i];
        if (s + a[i] <= 500) {
            s += a[i];
            std::cout << 'A';
        } else {
            s -= b[i];
            std::cout << 'G';
        }
    }
    std::cout << '\n';
    
    return 0;
}
