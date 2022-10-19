// url:https://codeforces.com/contest/716/problem/B
// time:2021-07-07 15:41:08
// name:B-CompletetheWord

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    
    int n = s.length();
    for (int i = 0; i + 26 <= n; i++) {
        int cnt[26] = {};
        bool bad = false;
        for (int j = i; j < i + 26; j++) {
            if (s[j] != '?' && ++cnt[s[j] - 'A'] > 1) {
                bad = true;
            }
        }
        if (!bad) {
            for (int j = i, k = 0; j < i + 26; j++) {
                if (s[j] != '?') {
                    continue;
                }
                while (cnt[k] > 0) {
                    k++;
                }
                s[j] = 'A' + k;
                cnt[k]++;
            }
            std::replace(s.begin(), s.end(), '?', 'A');
            std::cout << s << "\n";
            return 0;
        }
    }
    
    std::cout << "-1\n";
    
    return 0;
}
