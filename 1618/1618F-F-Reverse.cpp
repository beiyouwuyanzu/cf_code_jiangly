// url:https://codeforces.com/contest/1618/problem/F
// time:2021-12-22 10:41:32
// name:F-Reverse

#include <bits/stdc++.h>

using i64 = long long;

auto toBinary(i64 x) {
    std::vector<int> a;
    while (x) {
        a.push_back(x % 2);
        x /= 2;
    }
    std::reverse(a.begin(), a.end());
    return a;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    i64 x, y;
    std::cin >> x >> y;
    
    auto a = toBinary(x);
    auto b = toBinary(y);
    
    auto check = [&](auto a, auto b) {
        int n = a.size(), m = b.size();
        for (int _ = 0; _ < 2; _++) {
            for (int i = 0; i <= m - n; i++) {
                auto c = a;
                c.insert(c.begin(), i, 1);
                c.resize(m, 1);
                if (c == b) {
                    return true;
                }
            }
            std::reverse(a.begin(), a.end());
        }
        return false;
    };
    
    if (x == y) {
        std::cout << "YES\n";
        return 0;
    }
    
    if (b.back() == 0) {
        std::cout << "NO\n";
        return 0;
    }
    
    a.push_back(1);
    
    if (check(a, b)) {
        std::cout << "YES\n";
        return 0;
    }
    
    a.pop_back();
    while (a.back() == 0) {
        a.pop_back();
    }
    
    if (check(a, b)) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
    
    return 0;
}
