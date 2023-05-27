// url:https://codeforces.com/contest/112/problem/A
// time:2023-04-27 10:23:53
// name:A-PetyaandStrings

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s, t;
    std::cin >> s >> t;
    
    auto f = [](char &c) {
        if (std::isupper(c)) {
            c = std::tolower(c);
        }
    };
    
    std::ranges::for_each(s, f);
    std::ranges::for_each(t, f);
    
    if (s < t) {
        std::cout << -1 << "\n";
    } else if (s > t) {
        std::cout << 1 << "\n";
    } else {
        std::cout << 0 << "\n";
    }
    
    return 0;
}
