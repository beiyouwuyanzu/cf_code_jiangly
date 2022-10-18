//url:https://codeforces.com/contest/801/problem/A
//time:2021-01-03 17:19:44
//name:A-ViciousKeyboard

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string s;
    std::cin >> s;
    int n = s.length();
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'V' && s[i + 1] == 'K') {
            ans++;
        }
    }
    bool add = false;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'V' && s[i + 1] == 'V' && (i == n - 2 || s[i + 2] == 'V')) {
            add = true;
        }
        if (s[i] == 'K' && s[i + 1] == 'K' && (i == 0 || s[i - 1] == 'K')) {
            add = true;
        }
    }
    if (add) {
        ans++;
    }
    std::cout << ans << "\n";
    return 0;
}
