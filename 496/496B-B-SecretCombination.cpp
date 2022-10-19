// url:https://codeforces.com/contest/496/problem/B
// time:2021-06-20 20:45:35
// name:B-SecretCombination

#include <bits/stdc++.h>
using i64 = long long;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::string ans(s);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            ans = std::min(ans, s);
            for (int k = 0; k < n; k++) {
                if (s[k] == '9') {
                    s[k] = '0';
                } else {
                    s[k]++;
                }
            }
        }
        std::rotate(s.begin(), s.begin() + 1, s.end());
    }
    std::cout << ans << "\n";
    return 0;
}
