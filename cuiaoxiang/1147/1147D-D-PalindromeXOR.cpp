// url:https://codeforces.com/contest/1147/problem/D
// time:2022-03-15 17:53:58
// name:D-PalindromeXOR

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

const int N = 4e3 + 10;
int f[N];
int find(int x) {
  if (f[x] != f[f[x]]) f[x] = find(f[x]);
  return f[x];
}
void join(int x, int y) {
  int rx = find(x), ry = find(y);
  if (rx != ry) {
    f[ry] = rx;
  }
}

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
  string s;
  cin >> s;
  int n = SZ(s);
  reverse(s.begin(), s.end());

  auto solve =
    [&](int n, int m) -> int64 {
      int offset = n + m;
      for (int i = 0; i < (n + m) * 2; ++i) f[i] = i;
      for (int i = 0; i < n / 2; ++i) {
        int x = i, y = n - 1 - i;
        join(x, y);
        join(x + offset, y + offset);
      }
      for (int i = 0; i < m / 2; ++i) {
        int x = n + i, y = n + m - 1 - i;
        join(x, y);
        join(x + offset, y + offset);
      }
      for (int i = 0; i < m; ++i) {
        if (s[i] == '0') {
          join(i, n + i);
          join(i + offset, n + i + offset);
        } else if (s[i] == '1') {
          join(i, n + i + offset);
          join(i + offset, n + i);
        }
      }
      vector<int> bad(offset * 2);
      bad[0] = bad[n] = 1;
      for (int i = m; i < n; ++i) {
        if (s[i] == '0') {
          bad[i + offset] = 1;
        } else if (s[i] == '1') {
          bad[i] = 1;
        }
      }
      for (int i = 0; i < offset * 2; ++i) {
        if (bad[i]) bad[find(i)] = 1;
      }
      int ret = 1;
      for (int i = 0; i < offset; ++i) {
        int ri = find(i);
        int rj = find(i + offset);
        if (ri == rj) return 0;
        if (ri == i) {
          ret = ret * (2LL - bad[ri] - bad[rj]) % MOD;
        }
      }
      trace(m, ret);
      return ret;
    };
  int ret = 0;
  for (int m = 1; m < n; ++m) {
    add_mod(ret, solve(n, m));
  }
  cout << ret << '\n';

  return 0;
}

