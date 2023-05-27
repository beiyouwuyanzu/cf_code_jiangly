// url:https://codeforces.com/contest/282/problem/E
// time:2023-04-27 09:07:26
// name:E-SausageMaximization

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 100000 * 40;

int trie[N][2];
int cnt = 1;

void add(i64 x) {
    int p = 1;
    for (int i = 39; i >= 0; i--) {
        int d = x >> i & 1;
        if (!trie[p][d]) {
            trie[p][d] = ++cnt;
        }
        p = trie[p][d];
    }
}

i64 query(i64 x) {
    int p = 1;
    i64 ans = 0;
    for (int i = 39; i >= 0; i--) {
        int d = ~x >> i & 1;
        if (!trie[p][d]) {
            d ^= 1;
        } else {
            ans |= 1LL << i;
        }
        p = trie[p][d];
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::vector<i64> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    
    std::vector<i64> s(n+1);
    for (int i = 0; i < n; i++) {
        s[i+1] = s[i] ^ a[i];
    }
    
    i64 ans = 0;
    for (int i = 0; i <= n; i++) {
        add(s[i]);
        ans = std::max(ans, query(s[i] ^ s[n]));
    }
    std::cout << ans << "\n";
    
    return 0;
}
