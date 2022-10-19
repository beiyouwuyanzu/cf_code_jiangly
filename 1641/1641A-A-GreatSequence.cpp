// url:https://codeforces.com/contest/1641/problem/A
// time:2022-02-23 13:14:11
// name:A-GreatSequence

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, x;
    std::cin >> n >> x;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::multiset<int> s;
    
    std::sort(a.begin(), a.end());
    for (auto v : a) {
        if (v % x == 0 && s.find(v / x) != s.end()) {
            s.erase(s.find(v / x));
        } else {
            s.insert(v);
        }
    }
    
    std::cout << s.size() << "\n";
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
