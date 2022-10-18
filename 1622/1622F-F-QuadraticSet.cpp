//url:https://codeforces.com/contest/1622/problem/F
//time:2022-06-09 16:51:52
//name:F-QuadraticSet

#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<int> minp(n + 1);
    std::vector<int> primes;
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
            if (i % p == 0) {
                break;
            }
        }
    }
    
    std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::vector<u64> g(n + 1), f(n + 1);
    for (int i = 1; i <= n; i++) {
        g[i] = rng();
    }
    u64 h = 0;
    for (int i = 1; i <= n; i++) {
        int x = i;
        while (x > 1) {
            int p = minp[x];
            x /= p;
            h ^= g[p];
        }
        f[i] = h;
    }
    
    u64 all = 0;
    for (int i = 1; i <= n; i++) {
        all ^= f[i];
    }
    
    std::vector<bool> use(n + 1, true);
    if (all == 0) {
        // do nothing
    } else if (std::find(f.begin(), f.end(), all) != f.end()) {
        use[std::find(f.begin(), f.end(), all) - f.begin()] = false;
    } else {
        std::map<u64, int> index;
        for (int i = 1; i <= n; i++) {
            index[f[i]] = i;
        }
        bool two = false;
        for (int i = 1; i <= n; i++) {
            if (index.contains(f[i] ^ all)) {
                use[i] = use[index[f[i] ^ all]] = false;
                two = true;
                break;
            }
        }
        
        if (!two) {
            use[n] = use[n / 2] = use[2] = false;
        }
    }
    
    std::vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (use[i]) {
            ans.push_back(i);
        }
    }
    
    std::cout << ans.size() << "\n";
    for (auto x : ans) {
        std::cout << x << " \n"[x == ans.back()];
    }
    
    return 0;
}
