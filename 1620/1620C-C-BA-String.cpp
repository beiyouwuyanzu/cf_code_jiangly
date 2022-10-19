// url:https://codeforces.com/contest/1620/problem/C
// time:2021-12-18 20:08:16
// name:C-BA-String

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    i64 x;
    std::cin >> n >> k >> x;
    x--;
    
    std::string s;
    std::cin >> s;
    
    std::reverse(s.begin(), s.end());
    
    std::string t;
    int cnt = 0;
    for (auto c : s) {
        if (c == 'a') {
            t += std::string(x % (cnt * k + 1), 'b');
            x /= (cnt * k + 1);
            t += c;
            cnt = 0;
        } else {
            cnt++;
        }
    }
    t += std::string(x % (cnt * k + 1), 'b');
    x /= (cnt * k + 1);
    
    std::reverse(t.begin(), t.end());
    std::cout << t << "\n";
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

