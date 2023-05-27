// url:https://codeforces.com/contest/158/problem/C
// time:2023-04-26 19:50:06
// name:C-Cdandpwdcommands

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::string> a;
    
    while (n--) {
        std::string o;
        std::cin >> o;
        
        if (o == "pwd") {
            for (auto s : a) {
                std::cout << "/" << s;
            }
            std::cout << "/\n";
        } else {
            std::string s;
            std::cin >> s;
            int i = 0;
            while (true) {
                int j = s.find('/', i);
                if (!j) {
                    a.clear();
                } else if (j == -1) {
                    std::string t = s.substr(i);
                    if (t == "..") {
                        a.pop_back();
                    } else {
                        a.push_back(t);
                    }
                    break;
                } else {
                    std::string t = s.substr(i, j - i);
                    if (t == "..") {
                        a.pop_back();
                    } else {
                        a.push_back(t);
                    }
                }
                i = j+1;
            }
        }
    }
    
    return 0;
}
