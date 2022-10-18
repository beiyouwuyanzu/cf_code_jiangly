//url:https://codeforces.com/contest/1091/problem/C
//time:2021-07-15 21:21:08
//name:C-NewYearandtheSphereTransmission

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::set<i64> s;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            s.insert(i64(n / i) * (n / i - 1) / 2 * i + n / i);
            if (i * i != n) {
                s.insert(i64(i) * (i - 1) / 2 * (n / i) + i);
            }
        }
    }
    
    for (auto x : s) {
        std::cout << x << " ";
    }
    
    return 0;
}
