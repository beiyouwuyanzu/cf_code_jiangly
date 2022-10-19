// url:https://codeforces.com/contest/724/problem/A
// time:2021-12-22 11:04:10
// name:A-CheckingtheCalendar

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string a, b;
    std::cin >> a >> b;
    
    auto toInt = [&](auto s) {
        if (s == "monday") {
            return 0;
        } else if (s == "tuesday") {
            return 1;
        } else if (s == "wednesday") {
            return 2;
        } else if (s == "thursday") {
            return 3;
        } else if (s == "friday") {
            return 4;
        } else if (s == "saturday") {
            return 5;
        } else {
            return 6;
        }
    };
    
    auto x = toInt(a);
    auto y = toInt(b);
    
    for (auto v : {28, 30, 31}) {
        if (y == (x + v) % 7) {
            std::cout << "YES\n";
            return 0;
        }
    }
    
    std::cout << "NO\n";
    
    return 0;
}
