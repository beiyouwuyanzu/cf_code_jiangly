//url:https://codeforces.com/contest/1505/problem/C
//time:2021-04-01 18:12:13
//name:C-FibonacciWords

#include <bits/stdc++.h>
using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    for (int i = 2; i < int(s.length()); i++) {
        if ((s[i] - 'A') != (s[i - 1] - 'A' + s[i - 2] - 'A') % 26) {
            std::cout << "NO\n";
            return 0;
        }
    }
    std::cout << "YES\n";
    return 0;
}

