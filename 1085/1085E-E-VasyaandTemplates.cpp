//url:https://codeforces.com/contest/1085/problem/E
//time:2021-07-15 11:45:53
//name:E-VasyaandTemplates

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int k;
    std::cin >> k;
    
    std::string s, a, b;
    std::cin >> s >> a >> b;
    
    std::vector<int> p(k, -1), q(k, -1);
    
    auto print = [&]() {
        std::string ans;
        for (int i = 0, j = 0; i < k; i++) {
            if (p[i] >= 0) {
                ans += 'a' + p[i];
            } else {
                while (q[j] >= 0) {
                    j++;
                }
                ans += 'a' + j++;
            }
        }
        
        std::cout << "YES\n";
        std::cout << ans << "\n";
    };
    
    auto match = [&](int x, int y) {
        if (p[x] >= 0 && p[x] != y) {
            return false;
        }
        if (q[y] >= 0 && q[y] != x) {
            return false;
        }
        
        p[x] = y;
        q[y] = x;
        
        return true;
    };
    
    int n = s.length();
    bool diff = false;
    for (int i = 0; i < n; i++) {
        for (int c = a[i] - 'a' + 1; c <= (diff ? k - 1 : b[i] - 'a' - 1); c++) {
            if (match(s[i] - 'a', c)) {
                print();
                return;
            }
        }
        
        if (!match(s[i] - 'a', a[i] - 'a')) {
            break;
        }
        
        if (a[i] != b[i]) {
            diff = true;
        }
        
        if (i == n - 1) {
            print();
            return;
        }
    }
    
    diff = false;
    p.assign(k, -1);
    q.assign(k, -1);
    
    for (int i = 0; i < n; i++) {
        for (int c = (diff ? 0 : a[i] - 'a' + 1); c <= b[i] - 'a' - 1; c++) {
            if (match(s[i] - 'a', c)) {
                print();
                return;
            }
        }
        
        if (!match(s[i] - 'a', b[i] - 'a')) {
            break;
        }
        
        if (a[i] != b[i]) {
            diff = true;
        }
        
        if (i == n - 1) {
            print();
            return;
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
