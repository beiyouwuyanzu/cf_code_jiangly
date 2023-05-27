// url:https://codeforces.com/contest/706/problem/D
// time:2023-03-15 08:47:31
// name:D-Vasiliy'sMultiset

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 200000 * 30;

int trie[N][2];
int sum[N];
int cnt = 1;

void add(int x, int t) {
    int p = 1;
    sum[p] += t;
    for (int i = 29; i >= 0; i--) {
        int d = x >> i & 1;
        if (!trie[p][d]) {
            trie[p][d] = ++cnt;
        }
        p = trie[p][d];
        sum[p] += t;
    }
}

int query(int x) {
    int ans = 0;
    int p = 1;
    for (int i = 29; i >= 0; i--) {
        int d = x >> i & 1;
        if (sum[trie[p][!d]]) {
            p = trie[p][!d];
            ans |= 1 << i;
        } else {
            p = trie[p][d];
        }
    }
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int q;
    std::cin >> q;
    
    add(0, 1);
    for (int i = 0; i < q; i++) {
        char t;
        int x;
        std::cin >> t >> x;
        
        if (t == '+') {
            add(x, 1);
        } else if (t == '-') {
            add(x, -1);
        } else {
            std::cout << query(x) << "\n";
        }
    }
    
    return 0;
}

