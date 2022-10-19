// url:https://codeforces.com/contest/1530/problem/E
// time:2021-07-17 18:16:20
// name:E-Minimax

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s;
    std::cin >> s;
    
    int n = s.length();
    
    int cnt[26] = {};
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }
    
    if (s == std::string(n, s[0])) {
        std::cout << s << "\n";
        return;
    }
    
    int x = 0;
    while (x < 26 && cnt[x] != 1) {
        x++;
    }
    
    if (x < 26) {
        std::swap(s[0], s[s.find('a' + x)]);
        std::sort(s.begin() + 1, s.end());
        std::cout << s << "\n";
        return;
    }
    
    x = 0;
    while (cnt[x] == 0) {
        x++;
    }
    
    std::string t;
    t += 'a' + x;
    cnt[x]--;
    
    if (cnt[x] <= n / 2) {
        t += 'a' + x;
        cnt[x]--;
        int y = x + 1;
        while (cnt[x] > 0) {
            while (cnt[y] == 0) {
                y++;
            }
            t += 'a' + y;
            cnt[y]--;
            t += 'a' + x;
            cnt[x]--;
        }
        while (int(t.length()) < n) {
            while (cnt[y] == 0) {
                y++;
            }
            t += 'a' + y;
            cnt[y]--;
        }
        std::cout << t << "\n";
        return;
    }
    
    int y = x + 1;
    while (cnt[y] == 0) {
        y++;
    }
    
    if (cnt[x] + cnt[y] == n - 1) {
        while (cnt[y]--) {
            t += 'a' + y;
        }
        while (cnt[x]--) {
            t += 'a' + x;
        }
        std::cout << t << "\n";
        return;
    }
    
    int z = y + 1;
    while (cnt[z] == 0) {
        z++;
    }
    
    t += 'a' + y;
    cnt[y]--;
    
    while (cnt[x]--) {
        t += 'a' + x;
    }
    
    t += 'a' + z;
    cnt[z]--;
    
    for (int i = y; i < 26; i++) {
        while (cnt[i]--) {
            t += 'a' + i;
        }
    }
    
    std::cout << t << "\n";
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
