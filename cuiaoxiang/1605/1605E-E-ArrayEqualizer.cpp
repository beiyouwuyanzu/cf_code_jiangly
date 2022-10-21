// url:https://codeforces.com/contest/1605/problem/E
// time:2021-11-12 19:10:59
// name:E-ArrayEqualizer

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
  int n;
  cin >> n;
  vector<int> c(n);
  for (int i = 0; i < n; ++i) cin >> c[i];
  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    if (i > 0) c[i] = x - c[i];
  }
  vector<array<int64, 2>> a(n + 1);
  a[1] = {1, 0};
  for (int i = 2; i <= n; ++i) a[i][1] = c[i - 1];
  for (int i = 1; i <= n; ++i) {
    for (int j = i + i; j <= n; j += i) {
      a[j][0] -= a[i][0];
      a[j][1] -= a[i][1];
    }
  }
  int m;
  cin >> m;
  vector<array<int, 2>> b(m);
  for (int i = 0; i < m; ++i) {
    cin >> b[i][0];
    b[i][0] = b[i][0] - c[0];
    b[i][1] = i;
  }
  sort(b.begin(), b.end());
  trace(a, b);

  // vector<int> sgn(n + 1, 1);
  vector<vector<int>> pos(m + 1);
  for (int i = 1; i <= n; ++i) {
    if (a[i][0] >= 0) {
      a[i] = {-a[i][0], -a[i][1]};
      // sgn[i] = -1;
    }
    auto [A, B] = a[i];
    // first index such that Ax+B <= 0
    int low = 0, high = m;
    while (low != high) {
      int mid = (low + high) / 2;
      if (b[mid][0] * A + B > 0) {
        low = mid + 1;
      } else {
        high = mid;
      }
    }
    pos[high].push_back(i);
  }
  trace(pos, a);

  int64 A = 0, B = 0;
  for (int j = 1; j <= n; ++j) {
    A += a[j][0];
    B += a[j][1];
  }
  trace(A, B);
  vector<int64> ret(m);
  for (int i = 0; i < m; ++i) {
    for (auto& j : pos[i]) {
      A -= a[j][0]; B -= a[j][1];
      a[j] = {-a[j][0], -a[j][1]};
      A += a[j][0]; B += a[j][1];
    }
    trace(i, A, B);
    ret[b[i][1]] = A * b[i][0] + B;
  }
  for (int i = 0; i < m; ++i) {
    cout << ret[i] << '\n';
  }


  return 0;
}

