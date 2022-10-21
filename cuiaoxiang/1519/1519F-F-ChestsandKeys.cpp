// url:https://codeforces.com/contest/1519/problem/F
// time:2021-11-01 14:00:09
// name:F-ChestsandKeys

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

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n), b(m);
  int sum = 0;
  for (auto& x : a) cin >> x, sum += x;
  for (auto& x : b) cin >> x, sum -= x;

  auto c = vect<int>(0, n, m);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> c[i][j];
    }
  }

  if (sum > 0) {
    cout << -1 << '\n';
    return 0;
  }

  vector<int> p(n + 1);
  p[0] = 1;
  for (int i = 0; i < n; ++i) p[i + 1] = p[i] * (a[i] + 1);
  auto dp = vect<int>(-1, p[n], n, m, 5);
  function<int(int, int, int, int)> solve =
    [&](int state, int x, int y, int rem) {
      vector<int> f(n);
      for (int i = 0, t = state; i < n; ++i) {
        f[i] = t % (a[i] + 1);
        t /= a[i] + 1;
      }
      trace(state, f, x, y, rem);
      if (x == n) {
        if (y == m - 1) {
          bool ok = true;
          for (int i = 0; i < n; ++i) {
            if (f[i] != a[i]) ok = false;
          }
          return ok ? 0 : inf<int>;
        }
        return solve(state, 0, y + 1, b[y + 1]);
      }
      int& ret = dp[state][x][y][rem];
      if (ret >= 0) return ret;
      ret = inf<int>;
      for (int k = 0; k <= rem && k + f[x] <= a[x]; ++k) {
        int cur = c[x][y] * (k > 0 ? 1 : 0) + solve(state + k * p[x], x + 1, y, rem - k);
        ckmin(ret, cur);
      }
      return ret;
    };
  int ret = solve(0, 0, 0, b[0]);
  cout << ret << '\n';

  return 0;
}

