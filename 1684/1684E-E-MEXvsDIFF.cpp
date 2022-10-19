// url:https://codeforces.com/contest/1684/problem/E
// time:2022-05-19 18:15:10
// name:E-MEXvsDIFF

#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, k;
    std::cin >> n >> k;
    
    std::map<int, int> cnt;
    for (int i = 0; i <= n; i++) {
        cnt[i] = 0;
    }
    
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }
    
    int ans = n;
    int nonzero = 0;
    for (auto [x, c] : cnt) {
        nonzero += c > 0;
    }
    
    std::priority_queue<int> q;
    int sum = 0, count = 0;
    
    int right = 0;
    
    for (auto it = cnt.rbegin(); it != cnt.rend(); it++) {
        auto [x, c] = *it;
        
        nonzero -= c > 0;
        right++;
        
        int rest = k - c;
        std::vector<int> b{c};
        if (rest >= x - nonzero) {
            while (!q.empty() && sum > rest) {
                b.push_back(q.top());
                sum -= q.top();
                count--;
                q.pop();
            }
            
            ans = std::min(ans, right - 1 - count);
        }
        for (auto x : b) {
            q.push(x);
            sum += x;
            count++;
        }
        
        while (sum > k) {
            sum -= q.top();
            count--;
            q.pop();
        }
    }
    
    std::cout << ans << "\n";
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
