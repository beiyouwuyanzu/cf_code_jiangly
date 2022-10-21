// url:https://codeforces.com/contest/1361/problem/B
// time:2022-04-03 10:27:33
// name:B-JohnnyandGrandmaster

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
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
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
  int cas;
  cin >> cas;
  while (cas--) {
    int n, p;
    cin >> n >> p;
    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      cnt[x]++;
    }
    if (p == 1) {
      cout << n % 2 << '\n';
      continue;
    }

    vector<ii> a;
    for (auto& [k, v] : cnt) a.push_back({k, v});

    n = SZ(a);

    vector<int64> pw(1, 1);
    while (pw.back() * p <= 1e6) pw.push_back(pw.back() * p);

    trace(a, pw);
    int i;
    for (i = n - 1; i >= 0; --i) {
      auto [k, v] = a[i];
      if (v % 2) {
        int64 sum = 1;
        for (int j = i - 1; j >= 0 && sum; --j) {
          int k = a[j + 1].first - a[j].first;
          if (k >= SZ(pw)) break;
          int64 used = min(1LL * a[j].second, sum * pw[k]);
          // a[j].second -= used;
          sum = sum * pw[k] - used;
          if (sum > 1e6) break;
        }
        trace(i, a, sum);
        if (sum) break;
        sum = 1;
        for (int j = i - 1; j >= 0 && sum; --j) {
          int k = a[j + 1].first - a[j].first;
          if (k >= SZ(pw)) break;
          int64 used = min(1LL * a[j].second, sum * pw[k]);
          a[j].second -= used;
          sum = sum * pw[k] - used;
          if (sum > 1e6) break;
        }
      }
    }
    trace(i, a);
    if (i < 0) {
      cout << 0 << '\n';
    } else {
      int ret = power_mod(p, a[i].first);
      for (int j = 0; j < i; ++j) {
        sub_mod(ret, power_mod(p, a[j].first) * a[j].second % MOD);
      }
      cout << ret << '\n';
    }
  }

  return 0;
}

