// url:https://codeforces.com/contest/1758/problem/E
// time:2022-11-25 20:21:47
// name:E-Tick,Tock

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

const int N = 4e5 + 10;
int f[N], d[N];
int h;

int find(int x) {
  int fx = f[x];
  if (fx != f[fx]) {
    f[x] = find(fx);
    d[x] = (d[fx] + d[x]) % h;
  }
  return f[x];
}

int component;
bool merge(int x, int y, int D) {
  int rx = find(x), ry = find(y);
  if (rx == ry) {
    return (d[x] + D) % h == d[y];
  }
  f[ry] = rx;
  d[ry] = ((d[x] + D - d[y]) % h + h) % h;
  --component;
  return 1;
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
  int cas;
  cin >> cas;
  while (cas--) {
    int n, m;
    cin >> n >> m >> h;
    auto a = vect<int>(0, n, m);
    int x = -1, y = -1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> a[i][j];
        if (x < 0 && a[i][j] >= 0) {
          x = i;
          y = j;
        }
      }
    }
    if (x < 0) {
      cout << power_mod(h, n + m - 1) << '\n';
      continue;
    }
    swap(a[0], a[x]);
    for (int i = 0; i < n; ++i) swap(a[i][0], a[i][y]);
    trace(a);
    auto id = vect<int>(-1, n, m);
    int len = 1;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if ((i == 0 || j == 0) && a[i][j] < 0) id[i][j] = len++;
      }
    }
    trace(id);
    for (int i = 0; i < len; ++i) f[i] = i, d[i] = 0;
    component = len;
    vector<int> v;
    bool ok = 1;
    for (int i = 1; i < n && ok; ++i) {
      for (int j = 1; j < m && ok; ++j) {
        if (a[i][j] < 0) continue;
        int y = id[0][j], z = id[i][0];
        int val = (a[0][0] + a[i][j]) % h;
        trace(i, j, val);
        if (y < 0 && z >= 0) {
          val = (val + h - a[0][j]) % h;
          if (!merge(0, z, (h - val) % h)) ok = 0;
        } else if (z < 0 && y >= 0) {
          val = (val + h - a[i][0]) % h;
          if (!merge(0, y, val)) ok = 0;
        } else if (y >= 0 && z >= 0) {
          if (!merge(z, y, val)) ok = 0;
        } else {
          if (val != (a[0][j] + a[i][0]) % h) ok = 0;
        }
      }
    }
    trace(ok);
    if (ok) {
      cout << power_mod(h, component - 1) << '\n';
    } else {
      cout << 0 << '\n';
    }
  }

  return 0;
}

