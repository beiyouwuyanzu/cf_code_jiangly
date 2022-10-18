//url:https://codeforces.com/contest/1545/problem/C
//time:2021-07-11 19:02:50
//name:C-AquaMoonandPermutations

#include <bits/stdc++.h>

constexpr int P = 998244353;
using i64 = long long;
// assume -P <= x < 2P
int norm(int x) {
    if (x < 0) {
        x += P;
    }
    if (x >= P) {
        x -= P;
    }
    return x;
}
template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Z {
    int x;
    Z(int x = 0) : x(norm(x)) {}
    int val() const {
        return x;
    }
    Z operator-() const {
        return Z(norm(P - x));
    }
    Z inv() const {
        assert(x != 0);
        return power(*this, P - 2);
    }
    Z &operator*=(const Z &rhs) {
        x = i64(x) * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
};

void solve() {
    int n;
    std::cin >> n;
    
    std::vector a(2 * n, std::vector<int>(n));
    std::vector cnt(n, std::vector<int>(n));
    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
            a[i][j]--;
            cnt[j][a[i][j]]++;
        }
    }
    
    std::vector<bool> vis(2 * n);
    std::vector<int> ind;
    
    while (true) {
        int c = -1;
        
        for (int i = 0; i < n; i++) {
            int j = std::find(cnt[i].begin(), cnt[i].end(), 1) - cnt[i].begin();
            if (j == n) {
                continue;
            }
            
            c = i;
            break;
        }
        
        if (c < 0) {
            break;
        }
        
        int r = -1;
        
        for (int i = 0; i < 2 * n; i++) {
            if (!vis[i] && cnt[c][a[i][c]] == 1) {
                r = i;
            }
        }
        
        vis[r] = true;
        for (int j = 0; j < n; j++) {
            cnt[j][a[r][j]]--;
        }
        ind.push_back(r);
        
        for (int i = 0; i < 2 * n; i++) {
            if (vis[i]) {
                continue;
            }
            bool same = false;
            for (int j = 0; j < n; j++) {
                if (a[r][j] == a[i][j]) {
                    same = true;
                    break;
                }
            }
            if (!same) {
                continue;
            }
            vis[i] = true;
            for (int j = 0; j < n; j++) {
                cnt[j][a[i][j]]--;
            }
        }
    }
    
    Z ans = 1;
    std::vector<int> col(2 * n, -1);
    for (int i = 0; i < 2 * n; i++) {
        if (vis[i]) {
            continue;
        }
        
        std::queue<int> que;
        que.push(i);
        vis[i] = true;
        col[i] = 0;
        
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            
            if (col[u] == 0) {
                ind.push_back(u);
            }
            
            for (int v = 0; v < 2 * n; v++) {
                if (vis[v]) {
                    continue;
                }
                bool same = false;
                for (int j = 0; j < n; j++) {
                    if (a[u][j] == a[v][j]) {
                        same = true;
                    }
                }
                if (same) {
                    col[v] = col[u] ^ 1;
                    vis[v] = true;
                    que.push(v);
                }
            }
        }
        
        ans *= 2;
    }
    
    
    std::cout << ans.val() << "\n";
    
    for (int i = 0; i < n; i++) {
        std::cout << ind[i] + 1 << " \n"[i == n - 1];
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
