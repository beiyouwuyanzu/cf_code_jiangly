// url:https://codeforces.com/contest/1823/problem/D
// time:2023-04-28 09:03:46
// name:D-UniquePalindromes

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::vector<int> x(k), c(k);
    for (int i = 0; i < k; i++) {
        std::cin >> x[i];
    }
    for (int i = 0; i < k; i++) {
        std::cin >> c[i];
    }
    
    if (c[0] > x[0]) {
        std::cout << "NO\n";
        return;
    }
    for (int i = 1; i < k; i++) {
        if (c[i] - c[i - 1] > x[i] - x[i - 1]) {
            std::cout << "NO\n";
            return;
        }
    }
    
    std::cout << "YES\n";
    
    std::string s = "abc";
    char lst = 'c';
    int res = 3;
    for (int i = 0; i < k; i++) {
        while (x[i] - s.size() > c[i] - res) {
            lst = lst == 'c' ? 'a' : lst + 1;
            s += lst;
        }
        while (s.size() < x[i]) {
            s += 'a' + i + 3;
            res++;
        }
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
