//url:https://codeforces.com/contest/1085/problem/F
//time:2021-07-15 12:14:03
//name:F-Rock-Paper-ScissorsChampion

#include <bits/stdc++.h>

using i64 = long long;

int readToken() {
    char x;
    std::cin >> x;
    if (x == 'R') {
        return 0;
    } else if (x == 'P') {
        return 1;
    } else {
        return 2;
    }
}

template <typename T>
struct Fenwick {
    const int n;
    std::vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    T sum(int x) {
        T ans = 0;
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, q;
    std::cin >> n >> q;
    
    std::set<int> s[3];
    std::vector<Fenwick<int>> fen(3, n);
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = readToken();
        fen[a[i]].add(i, 1);
        s[a[i]].insert(i);
    }
    
    auto answer = [&]() {
        int ans = 0;
        
        for (int i = 0; i < 3; i++) {
            if (s[(i + 1) % 3].empty()) {
                ans += fen[i].sum(n);
                continue;
            }
            
            if (s[(i + 2) % 3].empty()) {
                continue;
            }
            
            ans += fen[i].sum(n);
            
            int x = *s[(i + 1) % 3].begin(), y = *s[(i + 2) % 3].begin();
            if (x < y) {
                ans -= fen[i].rangeSum(x, y);
            }
            
            x = *s[(i + 1) % 3].rbegin();
            y = *s[(i + 2) % 3].rbegin();
            if (x > y) {
                ans -= fen[i].rangeSum(y, x);
            }
        }
        
        std::cout << ans << "\n";
    };
    
    answer();
    
    while (q--) {
        int p;
        std::cin >> p;
        p--;
        
        int x = readToken();
        
        fen[a[p]].add(p, -1);
        s[a[p]].erase(p);
        a[p] = x;
        fen[x].add(p, 1);
        s[x].insert(p);
        
        answer();
    }
    
    return 0;
}
