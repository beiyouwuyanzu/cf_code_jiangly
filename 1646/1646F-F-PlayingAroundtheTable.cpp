// url:https://codeforces.com/contest/1646/problem/F
// time:2022-03-04 19:41:54
// name:F-PlayingAroundtheTable

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<std::multiset<int>> c(n);
    int turns = 0;
    for (int i = 0; i < n; i++) {
        int cnt = 0;
        for (int j = 0; j < n; j++) {
            int x;
            std::cin >> x;
            x--;
            int t = (x - i + n) % n;
            if (x == i) {
                cnt++;
            }
            if (x == i && cnt == 2) {
                t = n;
            }
            turns += t;
            c[i].insert(t);
        }
    }
    
    turns /= n;
    
    std::cout << turns << "\n";
    while (turns--) {
        std::vector<int> v(n);
        for (int i = 0; i < n; i++) {
            auto it = std::prev(c[i].end());
            
            assert(*it != 0);
            
            v[i] = *it;
            c[i].erase(it);
        }
        for (int i = 0; i < n; i++) {
            std::cout << (i + v[i]) % n + 1 << " \n"[i == n - 1];
            c[(i + 1) % n].insert(v[i] - 1);
        }
    }
    
    return 0;
}
