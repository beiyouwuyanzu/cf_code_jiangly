// url:https://codeforces.com/contest/1823/problem/C
// time:2023-04-28 08:51:52
// name:C-StronglyComposite

#include <bits/stdc++.h>

using i64 = long long;

std::vector<int> minp, primes;

void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}


void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    int ans = 0;
    std::set<int> s;
    
    for (int i = 0; i < n; i++) {
        int x = a[i];
        while (x > 1) {
            int p = minp[x];
            x /= p;
            if (s.count(p)) {
                ans++;
                s.erase(p);
            } else {
                s.insert(p);
            }
        }
    }
    
    ans += s.size() / 3;
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    sieve(1E7);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
