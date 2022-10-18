//url:https://codeforces.com/contest/800/problem/D
//time:2021-01-03 16:31:23
//name:D-VaryingKibibits

#include <bits/stdc++.h>
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
constexpr int P = 1000000007, N = 1e6;
struct Data {
    int s0, s1, s2;
    Data(int s0 = 0, int s1 = 0, int s2 = 0) : s0(s0), s1(s1), s2(s2) {}
};
Data operator+(const Data &a, const Data &b) {
    return Data((i64(a.s0) * (b.s0) + a.s0 + b.s0) % P,
            (i64(a.s0) * b.s1 + i64(a.s1) * b.s0 + a.s1 + b.s1) % P,
            (i64(a.s0) * b.s2 + 2ll * a.s1 * b.s1 % P + i64(a.s2) * b.s0 + a.s2 + b.s2) % P);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Data> s(N);
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        s[x] = s[x] + Data(1, x, i64(x) * x % P);
    }
    for (int i = 1; i < N; i *= 10) {
        for (int j = N - 1; j >= 0; j--) {
            if (j / i % 10 != 9) {
                s[j] = s[j] + s[j + i];
            }
        }
    }
    std::vector<int> g(N);
    for (int i = 0; i < N; i++) {
        g[i] = s[i].s2;
    }
    for (int i = 1; i < N; i *= 10) {
        for (int j = 0; j < N; j++) {
            if (j / i % 10 != 9) {
                g[j] = (g[j] - g[j + i] + P) % P;
            }
        }
    }
    i64 ans = 0;
    for (int i = 0; i < N; i++) {
        ans ^= i64(i) * g[i];
    }
    std::cout << ans << "\n";
    return 0;
}
