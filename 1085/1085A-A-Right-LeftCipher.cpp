//url:https://codeforces.com/contest/1085/problem/A
//time:2021-07-15 11:15:40
//name:A-Right-LeftCipher

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string t;
    std::cin >> t;
    
    std::string s;
    for (int i = t.length() - 1, l = 0, r = t.length(); i >= 0; i--) {
        if (i % 2 == 0) {
            s += t[l++];
        } else {
            s += t[--r];
        }
    }
    
    std::reverse(s.begin(), s.end());
    std::cout << s << "\n";
    
    return 0;
}
