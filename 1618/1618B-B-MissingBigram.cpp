// url:https://codeforces.com/contest/1618/problem/B
// time:2021-12-22 10:19:15
// name:B-MissingBigram

#include <bits/stdc++.h>

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<std::string> s(n - 2);
    for (int i = 0; i < n - 2; i++) {
        std::cin >> s[i];
    }
    
    int j = n - 2;
    for (int i = 0; i < n - 3; i++) {
        if (s[i][1] != s[i + 1][0]) {
            j = i + 1;
        }
    }
    
    for (int i = 0; i < j; i++) {
        std::cout << s[i][0];
    }
    std::cout << s[j - 1][1];
    std::cout << (j == n - 2 ? 'a' : s[j][0]);
    for (int i = j; i < n - 2; i++) {
        std::cout << s[i][1];
    }
    std::cout << "\n";
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
