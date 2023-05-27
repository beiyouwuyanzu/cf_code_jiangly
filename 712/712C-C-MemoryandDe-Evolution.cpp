// url:https://codeforces.com/contest/712/problem/C
// time:2023-03-15 11:25:03
// name:C-MemoryandDe-Evolution

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int x, y;
    std::cin >> x >> y;
    
    int a[3] = {y, y, y};
    
    int ans = 0;
    while (a[0] != x) {
        a[0] = std::min(x, a[1] + a[2] - 1);
        std::rotate(a, a + 1, a + 3);
        ans += 1;
    }
    
    std::cout << ans << "\n";
    
    return 0;
}

