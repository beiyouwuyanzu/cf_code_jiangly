// url:https://codeforces.com/contest/611/problem/E
// time:2021-11-07 11:48:56
// name:E-NewYearandThreeMusketeers

#define LOCAL
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

typedef long long int64;
typedef pair<int, int> ii;
#define SZ(x) (int)((x).size())
template <typename T> static constexpr T inf = numeric_limits<T>::max() / 2;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;
mt19937 mrand(random_device{}());
int rnd(int x) { return mrand() % x; }
// mt19937_64 mrand(random_device{}());
// int64 rnd(int64 x) { return mrand() % x; }
template <class T> void out(const vector<T>& a) { for (int i = 0; i < SZ(a); ++i) cout << a[i] << " \n"[i + 1 == SZ(a)]; }
template <class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template <class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }
template <class T> void dedup(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
void add(int& x, int y) { x += y; if (x >= MOD) x -= MOD; }

struct fast_ios {
  fast_ios() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(10);
  };
} fast_ios_;

int main() {
  int n;
  cin >> n;
  vector<int> a(3);
  for (auto& x : a) cin >> x;
  sort(a.begin(), a.end());
  vector<int> b(n);
  for (auto& x : b) cin >> x;
  multiset<int> B(b.begin(), b.end());

  if (*B.rbegin() > a[0] + a[1] + a[2]) {
    cout << -1 << '\n';
    return 0;
  }

  auto kill =
    [&](int x) {
      auto it = B.upper_bound(x);
      if (it == B.begin()) return -1;
      --it;
      int ret = *it;
      B.erase(it);
      return ret;
    };
  int ret = 0;
  for (; SZ(B); ++ret) {
    if (*B.rbegin() <= a[1]) {
      for (int i = 0; i < 3; ++i) kill(a[i]);
    } else if (*B.rbegin() <= a[2]) {
      vector<int> c(3);
      bool ok = true;
      for (int i = 0; i < 3; ++i) {
        c[i] = kill(a[i]);
        if (c[i] < 0) ok = false;
      }
      if (!ok) {
        for (int i = 0; i < 3; ++i) if (c[i] != -1) B.insert(c[i]);
        kill(a[0] + a[1]); kill(a[2]);
      }
    } else if (*B.rbegin() <= a[0] + a[1]) {
      kill(a[0] + a[1]);
      kill(a[2]);
    } else if (*B.rbegin() <= a[0] + a[2]) {
      kill(a[0] + a[2]);
      kill(a[1]);
    } else if (*B.rbegin() <= a[1] + a[2]) {
      kill(a[1] + a[2]);
      kill(a[0]);
    } else {
      kill(a[0] + a[1] + a[2]);
    }
  }

  cout << ret << '\n';
  return 0;
}

