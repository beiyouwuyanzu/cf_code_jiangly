// url:https://codeforces.com/contest/1743/problem/D
// time:2022-10-17 17:57:31
// name:D-ProblemwithRandomTests

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    if (s.find('1') == std::string::npos) {
        std::cout << 0 << "\n";
        return 0;
    }
    
    int a = s.find('1');
    
    if (s.substr(a).find('0') == std::string::npos) {
        std::cout << s.substr(a) << "\n";
        return 0;
    }
    
    int b = a + s.substr(a).find('0');
    
    auto ans = s;
    
    for (int i = 0; i <= b - a; i++) {
        auto res = s;
        for (int j = 0; j + i < n; j++) {
            res[j + i] |= s[j];
        }
        ans = std::max(ans, res);
    }
    ans = ans.substr(ans.find('1'));
    std::cout << ans << "\n";
    
    return 0;
}
