//url:https://codeforces.com/contest/1729/problem/B
//time:2022-09-12 17:39:45
//name:B-DecodeString

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string t;
    std::cin >> t;
    
    std::string s;
    for (int i = n - 1; i >= 0; ) {
        if (t[i] == '0') {
            int x = (t[i - 2] - '0') * 10 + t[i - 1] - '0' - 1;
            s += 'a' + x;
            i -= 3;
        } else {
            s += 'a' + t[i] - '0' - 1;
            i--;
        }
    }
    std::reverse(s.begin(), s.end());
    std::cout << s << "\n";
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
