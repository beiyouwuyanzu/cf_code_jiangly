// url:https://codeforces.com/contest/1129/problem/B
// time:2022-04-29 13:32:17
// name:B-WrongAnswer

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

int64 check(vector<int>& a) {
  int n = SZ(a);
  vector<int64> pre(n + 1);
  for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + a[i];
  int64 ret = -inf<int64>;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      int64 cur = (pre[j] - pre[i]) * (j - i);
      if (ret < cur) {
        ret = cur;
        trace(j - i);
      }
    }
  }
  trace(pre[n]);

  int64 sum = 0, res = -inf<int64>, k = -1;
  for (int i = 0; i < n; ++i) {
    sum += a[i];
    if (sum < 0) {
      sum = 0;
      k = i;
    }
    ckmax(res, (i - k) * sum);
  }

  trace(ret, res);
  return ret - res;
}

int main() {
  int64 m;
  cin >> m;

  int k = min(1999, (int)sqrt(m) / 2);
  trace(k);
  ckmax(k, 1);
  int64 x, y;
  for (x = k; ; ++x) {
    if ((m + (k + 1) * x) % k == 0) {
      y = (m + (k + 1) * x) / k;
      trace(y, x, k);
      if (y > x + k + 1) break;
    }
  }
  trace(x, y, k * y - (k + 1) * x, m);

  vector<int> ret(k + 1);
  int r = x % k;
  int q = x / k;
  int sum = 0;
  for (int i = 0; i < k; ++i) {
    ret[i] = i < r ? q + 1 : q;
    sum += ret[i];
    ret[i] = -ret[i];
  }
  trace(sum, x);
  ret[k] = y;
  cout << SZ(ret) << '\n';
  out(ret);

  trace(check(ret), m);

  return 0;
}

