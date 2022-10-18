//url:https://codeforces.com/contest/1697/problem/D
//time:2022-06-12 18:02:20
//name:D-GuessTheString

#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    int k = 0;
    std::vector<int> a(n), p;
    
    for (int i = 0; i < n; i++) {
        std::vector<int> q(k);
        std::iota(q.begin(), q.end(), 0);
        
        std::sort(q.begin(), q.end(), [&](int i, int j) {
            return p[i] > p[j];
        });
        
        int l = 0, r = k;
        while (l < r) {
            int m = (l + r) / 2;
            
            std::cout << "? 2 " << p[q[m]] + 1 << " " << i + 1 << std::endl;
            
            int res;
            std::cin >> res;
            
            if (res == m + 1) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        
        if (l == k) {
            a[i] = k++;
            p.push_back(i);
        } else {
            a[i] = q[l];
            p[a[i]] = i;
        }
    }
    
    std::string t, s;
    for (int i = 0; i < k; i++) {
        std::cout << "? 1 " << p[i] + 1 << std::endl;
        char c;
        std::cin >> c;
        t += c;
    }
    
    for (int i = 0; i < n; i++) {
        s += t[a[i]];
    }
    
    std::cout << "! " << s << std::endl;
    
    return 0;
}

