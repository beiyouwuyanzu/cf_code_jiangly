// url:https://codeforces.com/contest/710/problem/B
// time:2021-07-07 22:05:50
// name:B-OptimalPointonaLine

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> x(n);
    for (int i = 0; i < n; i++) {
        std::cin >> x[i];
    }
    
    int m = (n - 1) / 2;
    std::nth_element(x.begin(), x.begin() + m, x.end());
    std::cout << x[m] << "\n";
    
    return 0;
}
