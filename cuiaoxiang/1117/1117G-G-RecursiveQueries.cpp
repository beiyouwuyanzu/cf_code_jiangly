// url:https://codeforces.com/contest/1117/problem/G
// time:2022-03-15 14:43:07
// name:G-RecursiveQueries

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
    c = vect<T>(0, n + 1);
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
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n), L(n), R(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  vector<array<int, 3>> b(q);
  for (int i = 0; i < q; ++i) cin >> b[i][0], --b[i][0];
  for (int i = 0; i < q; ++i) cin >> b[i][1], --b[i][1], b[i][2] = i;

  vector<vector<int>> ll(n), rr(n);
  vector<int> st;
  for (int i = 0; i < n; ++i) {
    while (SZ(st) && a[st.back()] < a[i]) st.pop_back();
    L[i] = SZ(st) ? st.back() + 1 : 0;
    ll[L[i]].push_back(i);
    st.push_back(i);
  }
  st.clear();
  for (int i = n - 1; i >= 0; --i) {
    while (SZ(st) && a[st.back()] < a[i]) st.pop_back();
    R[i] = SZ(st) ? st.back() - 1 : n - 1;
    rr[R[i]].push_back(i);
    st.push_back(i);
  }
  trace(a, L, R);

  vector<int64> ret(q);
  for (int i = 0; i < q; ++i) ret[i] = b[i][1] - b[i][0] + 1;

  {
    fenwick<int64> F(n), G(n);
    sort(b.begin(), b.end(),
         [](const auto& L, const auto& R) {
           return L[1] < R[1];
         });
    trace(b);
    int j = 0;
    for (int i = 0; i < n; ++i) {
      F.add(i + 1, 1);
      if (i - 1 >= 0) {
        for (auto& k : rr[i - 1]) {
          F.add(k + 1, -1);
          G.add(k + 1, R[k]);
        }
      }
      for (; j < q && b[j][1] == i; ++j) {
        // b[j][0] .. b[j][1]
        int64 S0 = F.query(b[j][1] + 1) - F.query(b[j][0]);
        int64 S1 = G.query(b[j][1] + 1) - G.query(b[j][0]);
        trace(i, b[j], S0, S1);
        ret[b[j][2]] += i * S0 + S1;
      }
    }
  }
  {
    fenwick<int64> F(n), G(n);
    sort(b.begin(), b.end(),
         [](const auto& L, const auto& R) {
           return L[0] > R[0];
         });
    int j = 0;
    for (int i = n - 1; i >= 0; --i) {
      F.add(i + 1, 1);
      if (i + 1 < n) {
        for (auto& k : ll[i + 1]) {
          F.add(k + 1, -1);
          G.add(k + 1, L[k]);
        }
      }
      for (; j < q && b[j][0] == i; ++j) {
        // b[j][0] .. b[j][1]
        int64 S0 = F.query(b[j][1] + 1) - F.query(b[j][0]);
        int64 S1 = G.query(b[j][1] + 1) - G.query(b[j][0]);
        ret[b[j][2]] -= i * S0 + S1;
      }
    }
  }

  out(ret);

  return 0;
}

