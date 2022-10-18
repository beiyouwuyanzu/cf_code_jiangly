//url:https://codeforces.com/contest/1617/problem/D2
//time:2021-12-25 11:11:06
//name:D2-TooManyImpostors(hardversion)

#include <bits/stdc++.h>

using i64 = long long;

int query(int a, int b, int c) {
    std::cout << "? " << a + 1 << " " << b + 1 << " " << c + 1 << std::endl;
    int ans;
    std::cin >> ans;
    return ans;
}

void solve() {
    int n;
    std::cin >> n;
    
    std::vector<int> f(n / 3);
    for (int i = 0; i < n / 3; i++) {
        f[i] = query(3 * i, 3 * i + 1, 3 * i + 2);
    }
    
    int p = 0;
    while (f[p] == f[p + 1]) {
        p++;
    }
    
    std::vector<int> c(n, -1);
    
    int a[2];
    if (query(3 * p + 1, 3 * p + 2, 3 * p + 3) != f[p]) {
        a[f[p]] = 3 * p;
        a[!f[p]] = 3 * p + 3;
    } else if (query(3 * p + 2, 3 * p + 3, 3 * p + 4) != f[p]) {
        a[f[p]] = 3 * p + 1;
        a[!f[p]] = 3 * p + 4;
    } else {
        a[f[p]] = 3 * p + 2;
        a[!f[p]] = 3 * p + 5;
    }
    
    c[a[0]] = 0;
    c[a[1]] = 1;
    
    for (int i = 3 * p; i < 3 * p + 6; i++) {
        if (c[i] == -1) {
            c[i] = query(a[0], a[1], i);
        }
    }
    
    for (int i = 0; i < n / 3; i++) {
        if (i == p || i == p + 1) {
            continue;
        }
        if (query(3 * i, 3 * i + 1, a[!f[i]]) == f[i]) {
            c[3 * i] = c[3 * i + 1] = f[i];
            c[3 * i + 2] = query(3 * i + 2, a[0], a[1]);
        } else {
            c[3 * i + 2] = f[i];
            c[3 * i] = query(3 * i, a[0], a[1]);
            c[3 * i + 1] = !c[3 * i];
        }
    }
    
    std::vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (c[i] == 0) {
            ans.push_back(i);
        }
    }
    
    std::cout << "! " << ans.size();
    for (auto x : ans) {
        std::cout << " " << x + 1;
    }
    std::cout << std::endl;
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

