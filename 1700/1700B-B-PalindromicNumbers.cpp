//url:https://codeforces.com/contest/1700/problem/B
//time:2022-06-19 12:12:04
//name:B-PalindromicNumbers

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::string a;
    std::cin >> a;
    
    std::string s, b;
    if (a[0] != '9') {
        s = std::string(n, '9');
    } else {
        s = std::string(n + 1, '1');
    }
    std::reverse(a.begin(), a.end());
    
    int v = 0;
    for (int i = 0; i < n; i++) {
        int t = s[i] - a[i] - v;
        if (t < 0) {
            t += 10;
            v = 1;
        } else {
            v = 0;
        }
        b += '0' + t;
    }
    std::reverse(b.begin(), b.end());
    
    std::cout << b << "\n";
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

