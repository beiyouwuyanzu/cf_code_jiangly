// url:https://codeforces.com/contest/1619/problem/B
// time:2021-12-20 17:56:00
// name:B-SquaresandCubes

#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> good;

void solve() {
    int n;
    std::cin >> n;
    
    std::cout << std::upper_bound(good.begin(), good.end(), n) - good.begin() << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    const int limit = 1E9;
    
    for (int i = 1; i * i <= limit; i++) {
        good.push_back(i * i);
    }
    for (int i = 1; i * i * i <= limit; i++) {
        good.push_back(i * i * i);
    }
    
    std::sort(good.begin(), good.end());
    good.erase(std::unique(good.begin(), good.end()), good.end());
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}

