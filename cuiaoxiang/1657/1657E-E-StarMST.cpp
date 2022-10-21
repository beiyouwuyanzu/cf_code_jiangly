// url:https://codeforces.com/contest/1657/problem/E
// time:2022-03-22 19:21:30
// name:E-StarMST

// #define LOCAL
#define _USE_MATH_DEFINES
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <complex>
#include <cmath>
#include <numeric>
#include <bitset>
#include <functional>
#include <random>
#include <ctime>

using namespace std;

template <typename A, typename B>
ostream& operator <<(ostream& out, const pair<A, B>& a) {
  out << "(" << a.first << "," << a.second << ")";
  return out;
}
template <typename T, size_t N>
ostream& operator <<(ostream& out, const array<T, N>& a) {
  out << "["; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "]";
  return out;
}
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "]";
  return out;
}
template <typename T, class Cmp>
ostream& operator <<(ostream& out, const set<T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "}";
  return out;
}
template <typename T, class Cmp>
ostream& operator <<(ostream& out, const multiset<T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& v : a) { out << (first ? "" : ", "); out << v; first = 0;} out << "}";
  return out;
}
template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}
#ifdef LOCAL
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...) 42
#endif
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << ": " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << ": " << arg1 << " |";
  __f(comma + 1, args...);
}

template <class T> auto vect(const T& v, int n) { return vector<T>(n, v); }
template <class T, class... D> auto vect(const T& v, int n, D... m) {
  return vector<decltype(vect(v, m...))>(n, vect(v, m...));
}

using int64 = long long;
using int128 = __int128_t;
using ii = pair<int, int>;
#define SZ(x) (int)((x).size())
template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
// const int MOD = 1e9 + 7;
const int MOD = 998244353;
// mt19937 mrand(random_device{}());
// int rnd(int x) { return mrand() % x; }
mt19937_64 mrand(random_device{}());
int64 rnd(int64 x) { return mrand() % x; }
int lg2(int64 x) { return sizeof(int64) * 8 - 1 - __builtin_clzll(x); }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

const int N = 300;
int fact[N], ifact[N], reciprocal[N];

struct comb_init {
  comb_init() {
    reciprocal[1] = 1;
    for (int i = 2; i < N; ++i) {
      reciprocal[i] = (MOD - MOD / i) * (int64)reciprocal[MOD % i] % MOD;
    }
    fact[0] = ifact[0] = 1;
    for (int i = 1; i < N; ++i) {
      fact[i] = (int64)fact[i - 1] * i % MOD;
      ifact[i] = (int64)ifact[i - 1] * reciprocal[i] % MOD;
    }
  }
} comb_init_;

int64 comb(int64 n, int64 m) {
  if (n < m || m < 0) return 0;
  return (int64)fact[n] * ifact[m] % MOD * ifact[n - m] % MOD;
}

int main() {
  int n, m;
  cin >> n >> m;
  auto p = vect<int>(1, m + 1, n);
  for (int x = 1; x <= m; ++x) {
    for (int k = 1; k < n; ++k) {
      p[x][k] = 1LL * p[x][k - 1] * x % MOD;
    }
  }

  auto dp = vect<int>(1, m + 1, n);
  for (int pos = n - 2; pos >= 0; --pos) {
    auto ndp = vect<int>(0, m + 1, n);
    for (int high = 1; high <= m; ++high) {
      for (int len = 0; len <= pos; ++len) {
        int x = high;
        add_mod(ndp[high][len], 1LL * dp[x][len + 1] * reciprocal[len + 1] % MOD * p[x][pos] % MOD);
        for (int x = high - 1; x >= 1; --x) {
          add_mod(ndp[high][len], 1LL * p[x][pos] * dp[x][1] % MOD);
        }
      }
    }
    swap(dp, ndp);
  }
  int ret = 1LL * dp[m][0] * fact[n - 1] % MOD;
  cout << ret << '\n';
  return 0;

  // auto dp = vect<int>(-1, n - 1, m + 1, n - 1);
  // function<int(int, int, int)> solve =
  //   [&](int pos, int high, int len) {
  //     if (pos == n - 1) return 1;
  //     int& ret = dp[pos][high][len];
  //     if (ret >= 0) return ret;
  //     ret = 0;
  //     for (int x = high; x >= 1; --x) {
  //       int cur;
  //       if (x == high) {
  //         cur = 1LL * p[x][pos] * solve(pos + 1, x, len + 1) % MOD * reciprocal[len + 1] % MOD;
  //       } else {
  //         cur = 1LL * p[x][pos] * solve(pos + 1, x, 1) % MOD;
  //       }
  //       add_mod(ret, cur);
  //     }
  //     // trace(pos, high, len, ret);
  //     return ret;
  //   };
  // int ret = solve(0, m, 0);
  // ret = 1LL * ret * fact[n - 1] % MOD;
  // cout << ret << '\n';
}

