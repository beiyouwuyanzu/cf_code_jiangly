//url:https://codeforces.com/contest/1735/problem/E
//time:2022-10-04 15:24:39
//name:E-HousePlanning

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> d1(n), d2(n);
    for (int i = 0; i < n; i++) {
        std::cin >> d1[i];
    }
    for (int i = 0; i < n; i++) {
        std::cin >> d2[i];
    }
    std::sort(d1.begin(), d1.end());
    std::sort(d2.begin(), d2.end());
    
    auto check = [&](int d) {
        std::multiset s1(d1.begin(), d1.end()), s2(d2.begin(), d2.end());
        
        std::vector<int> a;
        
        while ((!s1.empty() && *s1.rbegin() >= d) || (!s2.empty() && *s2.rbegin() >= d)) {
            if (!s1.empty() && *s1.rbegin() >= d && (s2.empty() || *s1.rbegin() > *s2.rbegin())) {
                int x = *s1.rbegin();
                if (!s2.contains(x - d)) {
                    return false;
                }
                s1.erase(s1.find(x));
                s2.erase(s2.find(x - d));
                a.push_back(x);
            } else {
                int x = *s2.rbegin();
                if (!s1.contains(x - d)) {
                    return false;
                }
                s2.erase(s2.find(x));
                s1.erase(s1.find(x - d));
                a.push_back(d - x);
            }
        }
        
        while (!s1.empty()) {
            int x = *s1.begin();
            if (!s2.contains(d - x)) {
                return false;
            }
            s1.erase(s1.find(x));
            s2.erase(s2.find(d - x));
            a.push_back(x);
        }
        const int offset = std::max(0, -*std::min_element(a.begin(), a.end()));
        
        std::cout << "YES\n";
        for (int i = 0; i < n; i++) {
            std::cout << a[i] + offset << " \n"[i == n - 1];
        }
        std::cout << offset << " " << d + offset << "\n";
        return true;
    };
    
    if (check(d1[0] + d2.back())) {
        return;
    }
    for (int i = 0; i < n; i++) {
        if (d1[i] <= d2.back()) {
            if (check(d2.back() - d1[i])) {
                return;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (d2[i] <= d1.back()) {
            if (check(d1.back() - d2[i])) {
                return;
            }
        }
    }
    std::cout << "NO\n";
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
