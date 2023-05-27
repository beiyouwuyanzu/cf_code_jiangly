// url:https://codeforces.com/contest/281/problem/A
// time:2023-04-28 20:35:59
// name:A-WordCapitalization

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    
    if (std::islower(s[0])) {
        s[0] = std::toupper(s[0]);
    }
    
    std::cout << s << "\n";
    
    return 0;
}
