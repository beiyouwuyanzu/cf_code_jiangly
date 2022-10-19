// url:https://codeforces.com/contest/708/problem/A
// time:2021-12-24 04:40:55
// name:A-LettersCyclicShift

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string s;
    std::cin >> s;
    
    const int n = s.length();
    
    int i = 0;
    while (i < n && s[i] == 'a') {
        i++;
    }
    if (i == n) {
        s[n - 1] = 'z';
    }
    int j = i;
    while (j < n && s[j] != 'a') {
        s[j]--;
        j++;
    }
    
    std::cout << s << "\n";
    
    return 0;
}
