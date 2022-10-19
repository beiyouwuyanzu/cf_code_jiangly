// url:https://codeforces.com/contest/1638/problem/E
// time:2022-02-14 19:01:15
// name:E-ColorfulOperations

#include <bits/stdc++.h>

using i64 = long long;

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
    
    std::vector<i64> add(n);
    
    std::map<int, int> s;
    s[0] = 0;
    s[n] = -1;
    
    auto split = [&](int x) {
        auto it = std::prev(s.upper_bound(x));
        s[x] = it->second;
    };
    
    Fenwick<i64> fen(n);
    
    auto rangeAdd = [&](int l, int r, i64 x) {
        fen.add(l, x);
        fen.add(r, -x);
    };
    
    for (int i = 0; i < q; i++) {
        std::string op;
        std::cin >> op;
        
        if (op == "Color") {
            int l, r, c;
            std::cin >> l >> r >> c;
            l--;
            c--;
            
            split(l);
            split(r);
            
            auto it = s.find(l);
            while (it->first != r) {
                rangeAdd(it->first, std::next(it)->first, add[it->second] - add[c]);
                it = s.erase(it);
            }
            
            s[l] = c;
        } else if (op == "Add") {
            int c, x;
            std::cin >> c >> x;
            c--;
            
            add[c] += x;
        } else {
            int j;
            std::cin >> j;
            j--;
            
            split(j);
            
            std::cout << fen.sum(j + 1) + add[s[j]] << "\n";
        }
    }
    
    return 0;
}
