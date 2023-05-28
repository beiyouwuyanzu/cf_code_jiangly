// url:https://codeforces.com/contest/1764/problem/D
// time:2022-11-26 18:12:15
// name:D-Doremy'sPeggingGame

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
int MOD;
// const int MOD = 1e9 + 7;
// const int MOD = 998244353;
mt19937_64 mrand(random_device{}());
int64 rnd(int64 x) { return mrand() % x; }
constexpr inline int lg2(int64 x) { return x == 0 ? -1 : sizeof(int64) * 8 - 1 - __builtin_clzll(x); }
constexpr inline int p2ceil(int64 x) { return 1 << (lg2(x - 1) + 1); }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
inline void add_mod(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }
inline void sub_mod(int& x, int y) { x += MOD - y; if (x >= MOD) x -= MOD; }
inline int mod(int x) { return x >= MOD ? x - MOD : x; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

int64 power_mod(int64 a, int64 n, int p = MOD) {
  int64 ret = 1;
  a %= p;
  for (; n; n >>= 1) {
    if (n & 1) ret = ret * a % p;
    a = a * a % p;
  }
  return ret;
}

int main() {
  int n;
  cin >> n >> MOD;
  vector<int> fact(n + 1), ifact(n + 1);
  fact[0] = 1;
  for (int i = 1; i <= n; ++i) fact[i] = 1LL * fact[i - 1] * i % MOD;
  for (int i = 0; i <= n; ++i) ifact[i] = power_mod(fact[i], MOD - 2);
  auto comb = [&](int n, int m) {
    return 1LL * fact[n] * ifact[m] % MOD * ifact[n - m] % MOD;
  };
  int ret = 0;
  if (n % 2 == 0) {
    add_mod(ret, fact[n - 2]);
  }
  trace(ret);
  for (int k = 2; k <= (n + 1) / 2; ++k) {
    for (int i = 2; i <= k; ++i) {
      int cur;
      if (n % 2 == 0) {
        cur = 1LL * comb(k - 2, i - 2) * k % MOD;
      } else {
        cur = 1LL * comb(k - 2, i - 2) * (k - 1) % MOD;
      }
      // trace(k, i, cur, 1LL * fact[n - 1 - i] * cur % MOD);
      add_mod(ret, 1LL * fact[n - 1 - i] * cur % MOD);
    }
  }
  // if (n % 2 == 0) {
  //   // int cur = 2LL * fact[n - 2] * ifact[n / 2 - 1] % MOD * ifact[n / 2 - 1] % MOD;
  //   add_mod(ret, fact[n - 2]);
  // }
  // for (int i = 1; i < n; ++i) {
  //   if (i * 2 > n) continue;
  //   for (int j = i + 1; j < n; ++j) {
  //     if ((j - i) * 2 >= n) continue;
  //     if ((n - j) * 2 > n) continue;
  //     // int x = i - 1, y = j - i - 1, z = n - j - 1;
  //     // int cur = 1LL * fact[x + y + z] * ifact[x] % MOD * ifact[y] % MOD * ifact[z] % MOD;
  //     // trace(0, i, j);
  //     add_mod(ret, fact[n - 3]);
  //   }
  // }
  ret = 1LL * ret * n % MOD;
  cout << ret << '\n';
  return 0;
}

