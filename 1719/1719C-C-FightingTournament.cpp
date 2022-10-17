//url:https://codeforces.com/contest/1719/problem/C
//time:2022-09-29 14:44:50
//name:C-FightingTournament

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::list<int> s;
    for (int i = 0; i < n; i++) {
        s.push_back(i);
    }
    
    int rounds = 0;
    std::vector<std::vector<int>> wins(n);
    
    while (a[s.front()] != n) {
        int x = s.front();
        s.pop_front();
        int y = s.front();
        s.pop_front();
        
        if (a[x] < a[y]) {
            std::swap(x, y);
        }
        s.push_front(x);
        wins[x].push_back(rounds++);
        s.push_back(y);
    }
    
    for (int i = 0; i < q; i++) {
        int x, k;
        std::cin >> x >> k;
        
        x--;
        int ans = std::lower_bound(wins[x].begin(), wins[x].end(), k) - wins[x].begin();
        
        if (a[x] == n && k > rounds) {
            ans += k - rounds;
        }
        
        std::cout << ans << "\n";
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
