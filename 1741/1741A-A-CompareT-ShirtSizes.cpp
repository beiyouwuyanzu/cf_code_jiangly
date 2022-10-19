// url:https://codeforces.com/contest/1741/problem/A
// time:2022-10-11 17:40:21
// name:A-CompareT-ShirtSizes

#include <bits/stdc++.h>

using i64 = long long;

int f(auto a) {
    if (a == "M") {
        return 0;
    } else if (a.back() == 'S') {
        return -int(a.length());
    } else {
        return a.length();
    }
}

void solve() {
    std::string a, b;
    std::cin >> a >> b;
    
    if (f(a) < f(b)) {
        std::cout << "<\n";
    } else if (f(a) == f(b)) {
        std::cout << "=\n";
    } else {
        std::cout << ">\n";
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

