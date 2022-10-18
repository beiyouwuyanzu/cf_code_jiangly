//url:https://codeforces.com/contest/1505/problem/E
//time:2021-04-01 18:21:33
//name:E-Cakewalk

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> s(n);
    for (int i = 0; i < n; i++) {
        std::cin >> s[i];
    }
    int x = 0, y = 0;
    int ans = s[0][0] == '*';
    int last = 1;
    while (x < n - 1 || y < m - 1) {
        int ox = x, oy = y;
        if (x == n - 1) {
            y++;
        } else if (y == n - 1) {
            x++;
        } else if (s[x + 1][y] == '*' && s[x][y + 1] != '*') {
            x++;
        } else if (s[x + 1][y] != '*' && s[x][y + 1] == '*') {
            y++;
        } else if (last == 0) {
            x++;
        } else {
            y++;
        }
        if (ox == x) {
            last = 1;
        } else {
            last = 0;
        }
        ans += s[x][y] == '*';
    }
    std::cout << ans << "\n";
    return 0;
}

