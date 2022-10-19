// url:https://codeforces.com/contest/725/problem/A
// time:2021-07-06 21:26:57
// name:A-JumpingBall

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::string s;
    std::cin >> s;
    
    int i = 0, j = n;
    while (i < n && s[i] == '<') {
        i++;
    }
    while (j > 0 && s[j - 1] == '>') {
        j--;
    }
    
    int ans = i + n - j;
    std::cout << ans << "\n";
    
    return 0;
}
