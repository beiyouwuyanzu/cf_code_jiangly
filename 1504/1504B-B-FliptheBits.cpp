//url:https://codeforces.com/contest/1504/problem/B
//time:2021-12-24 12:10:42
//name:B-FliptheBits

#include <bits/stdc++.h>

using i64 = long long;

auto flip(std::string s) {
    for (auto &c : s) {
        c = '0' ^ '1' ^ c;
    }
    return s;
}

void solve() {
    int n;
    std::cin >> n;
    
    std::string a, b;
    std::cin >> a >> b;
    
    int balance = 0;
    bool nice = true;
    int j = 0;
    for (int i = 2; i <= n; i += 2) {
        balance += a[i - 2] == '1' ? 1 : -1;
        balance += a[i - 1] == '1' ? 1 : -1;
        
        if (balance == 0) {
            auto s = a.substr(j, i - j);
            auto t = b.substr(j, i - j);
            if (s != t && s != flip(t)) {
                nice = false;
            }
            j = i;
        }
    }
    auto s = a.substr(j);
    auto t = b.substr(j);
    if (s != t) {
        nice = false;
    }
    
    if (nice) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
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
