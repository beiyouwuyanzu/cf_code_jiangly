// url:https://codeforces.com/contest/725/problem/B
// time:2021-07-06 21:32:15
// name:B-FoodonthePlane

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    i64 n;
    std::cin >> n;
    char s;
    std::cin >> s;
    
    n--;
    i64 ans = n / 4 * 16;
    n %= 4;
    if (n == 1 || n == 3) {
        ans += 7;
    }
    if (s >= 'd') {
        ans += 'f' - s + 1;
    } else {
        ans += s - 'a' + 4;
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
