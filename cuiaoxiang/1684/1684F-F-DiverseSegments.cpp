// url:https://codeforces.com/contest/1684/problem/F
// time:2022-05-19 20:43:47
// name:F-DiverseSegments

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

template<typename T=int>
struct fenwick {
  vector<T> c;
  int n;
  fenwick(int n): n(n) {
    c = vect<T>(T(), n + 1);
  }
  void add(int x, T y) {
    if (x <= 0) return;
    for (; x <= n; x += x & -x) {
      ckmax(c[x], y);
    }
  }
  void update(int x1, int x2, T y) {
    add(x1, y);
    add(x2 + 1, -y);
  }
  T query(int x) {
    T ret = T();
    for (; x; x -= x & -x) {
      ckmax(ret, c[x]);
    }
    return ret;
  }
};

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int n, m;
    cin >> n >> m;
    map<int, vector<int>> pos;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      pos[x].push_back(i + 1);
    }

    fenwick F(n);
    for (int i = 0; i < m; ++i) {
      int L, R;
      cin >> L >> R;
      F.add(L, R);
    }
    vector<ii> A, B;
    for (auto& [k, v] : pos) {
      int L = 0, R = SZ(v) - 1;
      for (; L + 1 < SZ(v); ++L) {
        int x = v[L], y = v[L + 1];
        if (F.query(x) >= y) break;
      }
      for (; R - 1 >= 0; --R) {
        int x = v[R - 1], y = v[R];
        if (F.query(x) >= y) break;
      }
      if (L >= R) continue;
      if (F.query(v[L]) >= v[R]) {
        A.push_back({v[L], v[R - 1]});
        B.push_back({v[L + 1], v[R]});
      } else {
        A.push_back({v[L + 1], v[R - 1]});
        B.push_back({v[L + 1], v[R - 1]});
      }
    }
    trace(pos);
    trace(A, B);
    int ret = inf<int>;
    int len = SZ(A);
    for (int ll = 0; ll < n; ++ll) {
      bool ok = 1;
      int rr = ll - 1;
      for (int i = 0; i < len; ++i) {
        if (A[i].first >= ll) {
          ckmax(rr, A[i].second);
        } else if (B[i].first >= ll) {
          ckmax(rr, B[i].second);
        } else {
          ok = 0;
          break;
        }
      }
      if (!ok) break;
      ckmin(ret, rr - ll + 1);
    }
    cout << ret << '\n';
  }

  return 0;
}

