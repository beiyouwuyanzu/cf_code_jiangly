// url:https://codeforces.com/contest/1322/problem/B
// time:2022-03-25 15:47:22
// name:B-Present

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

template<typename T=int>
struct fenwick {
  vector<T> c;
  int n;
  fenwick(int n): n(n) {
    c = vect<T>(0, n + 1);
  }
  void add(int x, T y) {
    if (x <= 0) return;
    for (; x <= n; x += x & -x) {
      c[x] ^= y;
    }
  }
  void update(int x1, int x2, T y) {
    add(x1, y);
    add(x2 + 1, -y);
  }
  T query(int x) {
    T ret = 0;
    for (; x; x -= x & -x) {
      ret ^= c[x];
    }
    return ret;
  }
  T range(int L, int R) {
    return query(R) ^ query(L - 1);
  }
};

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  const int K = 25;
  const int N = 1 << K;

  int ret = 0;
  fenwick<char> F(N);
  for (int k = 0; k < K; ++k) {
    trace(k);
    int cur = 0;
    for (int i = n - 1; i >= 0; --i) {
      int x = (a[i] >> k) & 1;
      int y = a[i] & ((1 << k) - 1);
      int z = (1 << k) - 1 - y;
      int L, R;
      if (x == 0) {
        L = (1 << k) - y;
        R = (1 << k) + z;
        cur ^= F.range(L + 1, R + 1);
      } else {
        L = 0; R = z;
        cur ^= F.range(L + 1, R + 1);
        L = (1 << (k + 1)) - y;
        R = 1 << (k + 1);
        cur ^= F.range(L + 1, R + 1);
      }
      trace(i, a[i], a[i] & ((1 << (k + 1)) - 1));
      F.add((a[i] & ((1 << (k + 1)) - 1)) + 1, 1);
    }
    for (int i = 0; i < n; ++i) {
      F.add((a[i] & ((1 << (k + 1)) - 1)) + 1, 1);
    }
    trace(k, cur);
    ret |= cur << k;
  }
  cout << ret << '\n';
  return 0;
}

