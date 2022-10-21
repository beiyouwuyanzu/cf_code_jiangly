// url:https://codeforces.com/contest/710/problem/D
// time:2022-03-09 11:56:04
// name:D-TwoArithmeticProgressions

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
using ii = pair<int64, int64>;
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

int64 extended_gcd(int64 a, int64 b, int64& x, int64& y) {
  int64 t;
  if (b == 0)   {
    x = 1, y = 0;
    return a;
  }
  int64 d = extended_gcd(b, a % b, x, y);
  t = x, x = y;
  y = t - a / b * y;
  return d;
}

ii CRT_merge(ii A, ii B) {
  int64 s, t;
  int64 u = extended_gcd(B.first, A.first, s, t);
  if ((A.second - B.second) % u) return {0, 0};
  int64 v = (A.second - B.second) / u;
  int64 w = B.first / u;
  t = (-v * t % w + w) % w;
  return {A.first / gcd(A.first, B.first) * B.first, A.second + t * A.first};
}

int main() {
  int64 a1, b1, a2, b2, L, R;
  cin >> a1 >> b1 >> a2 >> b2 >> L >> R;

  ii ret = {a1, (b1 % a1 + a1) % a1};
  ret = CRT_merge(ret, ii{a2, (b2 % a2 + a2) % a2});
  auto [A, B] = ret;
  if (A == 0) {
    cout << 0 << '\n';
    return 0;
  }

  ckmax(L, b1);
  ckmax(L, b2);
  trace(L, R, A, B);
  auto mod =
    [&](int64 x, int64 y) {
      int64 ret = x % y;
      if (ret < 0) ret += y;
      return ret;
    };
  if (mod(R, A) < B) {
    R -= mod(R, A);
    R -= A - B;
  } else {
    R -= mod(R, A) - B;
  }
  if (mod(L, A) > B) {
    L += A - mod(L, A);
    L += B;
  } else {
    L += B - mod(L, A);
  }
  trace(L, R);
  if (R < L) {
    cout << 0 << '\n';
  } else {
    cout << (R - L) / A + 1 << '\n';
  }
  return 0;
}

