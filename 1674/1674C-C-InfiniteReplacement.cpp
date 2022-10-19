// url:https://codeforces.com/contest/1674/problem/C
// time:2022-05-02 17:45:24
// name:C-InfiniteReplacement

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    std::string s, t;
    std::cin >> s >> t;
    
    if (t == "a") {
        std::cout << "1\n";
        return;
    }
    
    if (std::count(t.begin(), t.end(), 'a') > 0) {
        std::cout << "-1\n";
        return;
    }
    
    std::cout << (1LL << s.length()) << "\n";
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
