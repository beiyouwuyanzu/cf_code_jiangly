// url:https://codeforces.com/contest/494/problem/A
// time:2021-06-21 18:11:46
// name:A-Treasure

#include <bits/stdc++.h>
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    int n = s.size();
    int open = std::count(s.begin(), s.end(), '(');
    int close = n - open;
    int balance = open - close;
    int sharp = std::count(s.begin(), s.end(), '#');
    if (balance < 0) {
        std::cout << "-1\n";
        return 0;
    }
    std::vector<int> a(sharp, 1);
    a.back() += balance;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '#') {
            s.insert(s.begin() + i, balance, ')');
            break;
        }
    }
    balance = 0;
    for (auto c : s) {
        if (c == '(') {
            balance++;
        } else {
            balance--;
        }
        if (balance < 0) {
            std::cout << "-1\n";
            return 0;
        }
    }
    for (auto x : a) {
        std::cout << x << "\n";
    }
    return 0;
}
