//url:https://codeforces.com/contest/1616/problem/B
//time:2021-12-29 18:42:13
//name:B-MirrorintheString

#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    if (n == 1 || s[0] <= s[1]) {
        std::cout << s[0] << s[0] << "\n";
    } else {
        int i = 1;
        while (i < n && s[i] <= s[i - 1]) {
            i++;
        }
        s = s.substr(0, i);
        std::cout << s;
        std::reverse(s.begin(), s.end());
        std::cout << s << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

