// url:https://codeforces.com/contest/236/problem/A
// time:2023-04-30 11:28:56
// name:A-BoyorGirl

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    
    if (std::set(s.begin(), s.end()).size() % 2) {
        std::cout << "IGNORE HIM!\n";
    } else {
        std::cout << "CHAT WITH HER!\n";
    }
    
    return 0;
}
