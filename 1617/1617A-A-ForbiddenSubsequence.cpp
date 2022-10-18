//url:https://codeforces.com/contest/1617/problem/A
//time:2021-12-25 11:24:46
//name:A-ForbiddenSubsequence

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s, t;
    std::cin >> s >> t;
    
    int cnt[26] = {};
    for (auto c : s) {
        cnt[c - 'a']++;
    }
    
    s = std::string(cnt[0], 'a');
    if (t == "abc" && cnt[0] > 0 && cnt[1] > 0 && cnt[2] > 0) {
        s += std::string(cnt[2], 'c');
        s += std::string(cnt[1], 'b');
    } else {
        s += std::string(cnt[1], 'b');
        s += std::string(cnt[2], 'c');
    }
    
    for (int i = 3; i < 26; i++) {
        s += std::string(cnt[i], 'a' + i);
    }
    
    std::cout << s << "\n";
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

