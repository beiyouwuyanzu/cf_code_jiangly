// url:https://codeforces.com/contest/1765/problem/A
// time:2022-11-27 15:14:14
// name:A-AccessLevels

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

struct Hungarian {
  int n;
  vector<vector<int>> a;
  vector<int> d;
  vector<bool> visit;
  bool path(int u) {
    for (auto& v : a[u]) {
      if (visit[v]) continue;
      visit[v] = true;
      if (d[v] < 0 || path(d[v])) {
        d[v] = u;
        return true;
      }
    }
    return false;
  }
  Hungarian(int n, int m) : n(n), a(n), d(m, -1), visit(m) {}
  void add_edge(int x, int y) {
    a[x].push_back(y);
  }
  int solve() {
    int ret = 0;
    for (int i = 0; i < n; ++i) {
      fill(visit.begin(), visit.end(), false);
      ret += path(i);
    }
    return ret;
  }
};

int main() {
  int n, m;
  cin >> n >> m;
  vector<string> s(n);
  for (int i = 0; i < n; ++i) cin >> s[i];
  const int N = 500;
  vector<bitset<N>> mask(m);
  for (int j = 0; j < m; ++j) {
    for (int i = 0; i < n; ++i) mask[j][i] = s[i][j] - '0';
  }
  Hungarian H(m, m);
  for (int j = 0; j < m; ++j) {
    for (int k = 0; k < m; ++k) {
      if (j == k) continue;
      if (mask[j] == mask[k]) {
        if (j < k) H.add_edge(j, k);
      } else {
        if ((mask[j] & mask[k]) == mask[k]) {
          H.add_edge(j, k);
        }
      }
    }
  }
  H.solve();
  vector<int> nxt(m, -1);
  for (int y = 0; y < m; ++y) {
    int x = H.d[y];
    if (x >= 0) nxt[x] = y;
  }
  vector<bool> vis(m);
  vector<vector<int>> chain;
  for (int i = 0; i < m; ++i) {
    if (vis[i]) continue;
    if (H.d[i] >= 0) continue;
    vector<int> cur;
    for (int t = i; t != -1 && !vis[t]; t = nxt[t]) {
      vis[t] = 1;
      cur.push_back(t);
    }
    chain.push_back(cur);
  }
  trace(chain);
  int len = SZ(chain);
  vector<int> label(m), score(m);
  for (int i = 0; i < len; ++i) {
    auto& v = chain[i];
    for (int j = 0; j < SZ(v); ++j) {
      int x = v[j];
      label[x] = i + 1;
      score[x] = j + 2;
    }
  }
  cout << len << '\n';
  out(label);
  out(score);
  for (int i = 0; i < n; ++i) {
    vector<int> ret(len, 1);
    for (int j = 0; j < m; ++j) {
      int k = label[j] - 1;
      if (s[i][j] == '1') ckmax(ret[k], score[j]);
    }
    out(ret);
  }
  return 0;
}

