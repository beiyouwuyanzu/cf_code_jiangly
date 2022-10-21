// url:https://codeforces.com/contest/1585/problem/E
// time:2022-03-14 15:00:37
// name:E-FrequencyQueries

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
template<size_t N> int find_first(const bitset<N>& x) {
#ifdef LOCAL
  int k; for (k = 0; k < N && !x[k]; ++k);
  return k;
#else
  return x._Find_first();
#endif
}

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
    c = vect<int>(0, n + 1);
  }
  void add(int x, T y) {
    if (x <= 0) return;
    for (; x <= n; x += x & -x) {
      c[x] += y;
    }
  }
  void update(int x1, int x2, T y) {
    add(x1, y);
    add(x2 + 1, -y);
  }
  T query(int x) {
    T ret = 0;
    for (; x; x -= x & -x) {
      ret += c[x];
    }
    return ret;
  }
  // find the largest index satisfy the accumulated frequency
  int find(int x) {
    trace("find", x, c);
    int cur = 0, step = 1;
    while (step * 2 <= n) step <<= 1;
    for (; step && cur < n; step >>= 1) {
      int nxt = cur + step;
      if (nxt <= n && x >= c[nxt]) {
        cur = nxt;
        x -= c[nxt];
      }
    }
    trace("find after", x, cur, c);
    return cur;
  }
};

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int n, q;
    cin >> n >> q;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) cin >> x[i];

    vector<vector<int>> a(n);
    for (int i = 1; i < n; ++i) {
      int j;
      cin >> j;
      --j;
      a[j].push_back(i);
    }

    vector<vector<array<int, 3>>> b(n);
    for (int i = 0; i < q; ++i) {
      int u, lev, k;
      cin >> u >> lev >> k;
      --u;
      b[u].push_back({lev, k, i});
    }

    vector<int> cnt(n + 1);
    vector<set<int>> c(n + 1);
    fenwick F(n);
    vector<int> ret(q, -1);
    function<void(int)> dfs =
      [&](int u) {
        int val = x[u];
        ++cnt[val];
        c[cnt[val] - 1].erase(val);
        c[cnt[val]].insert(val);
        F.add(cnt[val] - 1, -1);
        F.add(cnt[val], 1);
        trace(u, val, cnt);
        trace(c[1], c[2], c[3]);
        for (auto& [lev, k, id] : b[u]) {
          int offset = F.query(lev - 1);
          int x = F.find(offset + k - 1) + 1;
          trace(u, lev, k, id, offset, x);
          if (x <= n) ret[id] = *c[x].begin();
          trace(ret);
        }
        for (auto& v : a[u]) {
          dfs(v);
        }
        F.add(cnt[val], -1);
        F.add(cnt[val] - 1, 1);
        c[cnt[val]].erase(val);
        c[cnt[val] - 1].insert(val);
        --cnt[val];
      };

    dfs(0);
    out(ret);
  }

  return 0;
}

