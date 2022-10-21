// url:https://codeforces.com/contest/936/problem/B
// time:2022-03-17 13:59:52
// name:B-SleepyGame

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

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<int>> a(n), ra(n);
  for (int i = 0; i < n; ++i) {
    int len;
    cin >> len;
    while (len--) {
      int j;
      cin >> j;
      --j;
      a[i].push_back(j);
      ra[j].push_back(i);
    }
  }
  int s;
  cin >> s;
  --s;

  queue<ii> Q;
  auto visit = vect<bool>(0, n, 2);
  auto nxt = vect<ii>({-1, -1}, n, 2);
  for (int i = 0; i < n; ++i) {
    if (SZ(a[i]) == 0) {
      Q.push({i, 0});
      visit[i][0] = 1;
    }
  }

  while (!Q.empty()) {
    auto [u, k] = Q.front();
    Q.pop();
    for (auto& v : ra[u]) {
      int nk = k ^ 1;
      if (!visit[v][nk]) {
        visit[v][nk] = 1;
        nxt[v][nk] = {u, k};
        Q.push({v, nk});
      }
    }
  }

  trace(visit[s][0], visit[s][1]);

  vector<bool> color(n);
  function<bool(int)> rec =
    [&](int u) {
      color[u] = 1;
      for (auto& v : a[u]) {
        if (color[v]) {
          return true;
        } else {
          if (rec(v)) return true;
        }
      }
      color[u] = 0;
      return false;
    };

  if (visit[s][1]) {
    cout << "Win" << '\n';
    vector<int> ret;
    for (int u = s, k = 1; u != -1; ) {
      ret.push_back(u + 1);
      auto [v, nk] = nxt[u][k];
      u = v;
      k = nk;
    }
    out(ret);
  } else if (rec(s)) {
    cout << "Draw" << '\n';
  } else {
    cout << "Lose" << '\n';
  }
  return 0;
}

