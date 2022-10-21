// url:https://codeforces.com/contest/1167/problem/F
// time:2021-11-01 11:37:15
// name:F-ScalarQueries

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

template<typename T, size_t N>
struct fenwick {
  T c[N];
  fenwick() {
    fill(c + 1, c + N, 0);
  }
  void add(int x, T y) {
    for (; x < N; x += x & -x) {
      c[x] += y;
      if (c[x] >= MOD) c[x] -= MOD;
    }
  }
  T query(int x) {
    T ret = 0;
    for (; x; x -= x & -x) {
      ret += c[x];
      if (ret >= MOD) ret -= MOD;
    }
    return ret;
  }
};

int main() {
  int n;
  cin >> n;
  vector<array<int, 2>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i][0];
    a[i][1] = i + 1;
  }
  sort(a.begin(), a.end());

  const int N = 5e5 + 10;
  fenwick<int, N> F0, F1;

  int ret = 0, m0 = 0, m1 = 0;
  for (auto& [v, x] : a) {
    int S0 = F0.query(x);
    int S1 = F1.query(x);
    int T0 = m0 - S0;
    int T1 = (m1 + MOD - S1) % MOD;
    int cur = 1LL * S1 * (n + 1 - x) % MOD;
    trace(cur);
    add(cur, 1LL * (n + 1) * x % MOD * T0 % MOD);
    add(cur, MOD - 1LL * x * T1 % MOD);

    trace(x, S0, S1, T0, T1, cur);
    add(ret, 1LL * cur * v % MOD);
    add(ret, 1LL * x * (n + 1 - x) % MOD * v % MOD);

    m0 += 1;
    add(m1, x);
    F0.add(x, 1);
    F1.add(x, x);
  }
  cout << ret << '\n';
  return 0;
}

