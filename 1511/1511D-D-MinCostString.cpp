//url:https://codeforces.com/contest/1511/problem/D
//time:2022-09-22 13:59:15
//name:D-MinCostString

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, k;
    std::cin >> n >> k;
    
    const int m = (n - 1) / (k * k) + 1;
    
    std::vector<int> a;
    
    for (int i = 0; i < k; i++) {
        for (int j = k - 1; j > i; j--) {
            a.push_back(i);
            a.push_back(j);
        }
    }
    for (int i = k - 1; i >= 0; i--) {
        a.push_back(i);
    }
    
    for (int i = 0; i < n; i++) {
        std::cout << char('a' + a[i % (k * k)]);
    }
    std::cout << "\n";
    
    return 0;
}
