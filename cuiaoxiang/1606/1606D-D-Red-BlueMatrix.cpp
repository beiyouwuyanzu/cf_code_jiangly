// url:https://codeforces.com/contest/1606/problem/D
// time:2021-10-29 19:45:55
// name:D-Red-BlueMatrix

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

const int K = 1000000;

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        cin >> a[i][j];
      }
    }
    auto sufmax = vect<int>(0, n, m);
    auto sufmin = vect<int>(0, n, m);
    for (int i = 0; i < n; ++i) {
      sufmax[i][0] = 0; sufmin[i][0] = K + 1;
      for (int j = 1; j < m; ++j) {
        sufmax[i][j] = max(sufmax[i][j - 1], a[i][m - j]);
        sufmin[i][j] = min(sufmin[i][j - 1], a[i][m - j]);
      }
    }
    auto premax = vect<int>(0, n, m);
    auto premin = vect<int>(0, n, m);
    for (int i = 0; i < n; ++i) {
      premax[i][0] = 0; premin[i][0] = K + 1;
      for (int j = 1; j < m; ++j) {
        premax[i][j] = max(premax[i][j - 1], a[i][j - 1]);
        premin[i][j] = min(premin[i][j - 1], a[i][j - 1]);
      }
    }

    bool found = false;
    for (int k = 1; k < m && !found; ++k) {
      vector<array<int, 3>> b(n);
      for (int i = 0; i < n; ++i) {
        b[i] = {premin[i][k], premax[i][k], i};
      }
      sort(b.begin(), b.end());
      trace(k, b);
      vector<int> preL(n + 1), preR(n + 1, inf<int>);
      for (int i = 0; i < n; ++i) {
        preL[i + 1] = max(preL[i], b[i][1]);
        int x = b[i][2];
        preR[i + 1] = min(preR[i], sufmin[x][m - k]);
      }
      vector<int> sufL(n + 1, inf<int>), sufR(n + 1);
      for (int i = 0; i < n; ++i) {
        sufL[i + 1] = min(sufL[i], b[n - 1 - i][0]);
        int x = b[n - 1 - i][2];
        sufR[i + 1] = max(sufR[i], sufmax[x][m - k]);
      }
      trace(preL, preR, sufL, sufR);
      for (int i = 1; i < n && !found; ++i) {
        if (preL[i] < sufL[n - i] && preR[i] > sufR[n - i]) {
          cout << "YES" << '\n';
          string ret(n, 'R');
          for (int r = 0; r < i; ++r) {
            int x = b[r][2];
            ret[x] = 'B';
          }
          cout << ret << " " << k << '\n';
          found = true;
          break;
        }
      }
    }
    if (!found) cout << "NO" << '\n';
  }

  return 0;
}

