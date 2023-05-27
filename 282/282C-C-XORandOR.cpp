// url:https://codeforces.com/contest/282/problem/C
// time:2023-04-27 08:52:58
// name:C-XORandOR

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string a, b;
    std::cin >> a >> b;
    
    if (a.size() == b.size() && (a.find('1') != -1) == (b.find('1') != -1)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    
    return 0;
}
