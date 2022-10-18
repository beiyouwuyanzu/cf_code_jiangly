//url:https://codeforces.com/contest/709/problem/A
//time:2021-12-24 06:07:11
//name:A-Juicer

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, b, d;
    std::cin >> n >> b >> d;
    
    int ans = 0;
    
    int s = 0;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (x > b) {
            continue;
        }
        s += x;
        if (s > d) {
            ans++;
            s = 0;
        }
    }
    
    std::cout << ans << "\n";
    
    return 0;
}
