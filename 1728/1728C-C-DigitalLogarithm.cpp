//url:https://codeforces.com/contest/1728/problem/C
//time:2022-09-08 17:44:25
//name:C-DigitalLogarithm

#include <bits/stdc++.h>

using i64 = long long;

int f(int x) {
    return std::to_string(x).length();
}

void solve() {
    int n;
    std::cin >> n;
    
    std::priority_queue<int> a, b;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        a.push(x);
    }
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        b.push(x);
    }
    
    int ans = 0;
    
    while (!a.empty()) {
        int x = a.top();
        int y = b.top();
        
        if (x > y) {
            a.pop();
            a.push(f(x));
            ans++;
        } else if (x < y) {
            b.pop();
            b.push(f(y));
            ans++;
        } else {
            a.pop();
            b.pop();
        }
    }
    
    std::cout << ans << "\n";
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
