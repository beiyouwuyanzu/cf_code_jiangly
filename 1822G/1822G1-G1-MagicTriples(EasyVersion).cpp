// url:https://codeforces.com/contest/1822/problem/G1
// time:2023-04-25 15:33:25
// name:G1-MagicTriples(EasyVersion)

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

std::vector<std::vector<int>> divs;

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::sort(a.begin(), a.end());
    
    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        int s = 1;
        for (auto v : primes) {
            if (v * v * v > x) {
                break;
            }
            int t = 0;
            while (x % v == 0) {
                x /= v;
                t++;
                if (t % 2 == 0) {
                    s *= v;
                }
            }
        }
        if (x > 1) {
            int u = std::sqrt(x);
            if (u * u == x) {
                s *= u;
            }
        }
        
        for (auto b : divs[s]) {
            auto [l1, r1] = std::equal_range(a.begin(), a.end(), a[i] / b);
            auto [l2, r2] = std::equal_range(a.begin(), a.end(), a[i] / (b*b));
            
            ans += 1LL * (r1-l1) * (r2-l2);
        }
    }
    
    for (int i = 0, j = 0; i < n; i = j) {
        while (j < n && a[i] == a[j]) {
            j++;
        }
        ans += 1LL * (j-i) * (j-i-1) * (j-i-2);
    }
    
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n = 4E4;
    sieve(n);
    divs.resize(n+1);
    for (int i = 2; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            divs[j].push_back(i);
        }
    }
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
