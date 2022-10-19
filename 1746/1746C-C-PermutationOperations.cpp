// url:https://codeforces.com/contest/1746/problem/C
// time:2022-10-15 17:45:56
// name:C-PermutationOperations

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    for (int i = n - 1; i > 0; i--) {
        a[i] -= a[i - 1];
    }
    
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(), [&](int i, int j) {
        return a[i] > a[j];
    });
    
    for (int i = 0; i < n; i++) {
        std::cout << p[i] + 1 << " \n"[i == n - 1];
    }
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
