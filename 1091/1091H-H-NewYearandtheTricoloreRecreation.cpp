//url:https://codeforces.com/contest/1091/problem/H
//time:2021-07-16 10:44:24
//name:H-NewYearandtheTricoloreRecreation

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 200000;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, f;
    std::cin >> n >> f;
    
    std::vector<int> a;
    a.reserve(2 * n);
    
    for (int i = 0; i < n; i++) {
        int b, w, r;
        std::cin >> b >> w >> r;
        a.push_back(w - b - 1);
        a.push_back(r - w - 1);
    }
    
    std::vector<int> good;
    std::vector<bool> isGood(N);
    std::bitset<N> g;
    for (int i = 2; i < N; i++) {
        if (i == f) {
            continue;
        }
        int cnt = 0;
        int x = i;
        for (int j = 2; j * j <= x; j++) {
            while (x % j == 0) {
                x /= j;
                cnt++;
            }
        }
        cnt += (x > 1);
        
        if (cnt <= 2) {
            isGood[i] = true;
            good.push_back(i);
        }
    }
    
    std::vector<int> sg(N);
    std::vector<std::vector<int>> p;
    
    for (int i = 0; i < N; i++) {
        for (int v = 0; ; v++) {
            if (v == int(p.size())) {
                p.push_back({});
            }
            bool has = false;
            
            for (auto x : p[v]) {
                if (isGood[i - x]) {
                    has = true;
                    break;
                }
            }
            
            if (!has) {
                sg[i] = v;
                break;
            }
        }
        
        p[sg[i]].push_back(i);
    }
    
    int ans = 0;
    for (auto x : a) {
        ans ^= sg[x];
    }
    
    if (ans == 0) {
        std::cout << "Bob\n";
        std::cout << "Alice\n";
    } else {
        std::cout << "Alice\n";
        std::cout << "Bob\n";
    }
    
    return 0;
}
