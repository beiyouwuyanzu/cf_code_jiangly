// url:https://codeforces.com/contest/612/problem/A
// time:2023-04-24 10:23:31
// name:A-TheTextSplitting

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, p, q;
    std::cin >> n >> p >> q;
    
    std::string s;
    std::cin >> s;
    
    for (int i = 0; i*p <= n; i++) {
        if ((n - i*p) % q == 0) {
            std::cout << i + (n - i*p) / q << "\n";
            int j = 0;
            while (j < i*p) {
                std::cout << s.substr(j, p) << "\n";
                j += p;
            }
            while (j < n) {
                std::cout << s.substr(j, q) << "\n";
                j += q;
            }
            return 0;
        }
    }
    std::cout << -1 << "\n";
    
    return 0;
}
