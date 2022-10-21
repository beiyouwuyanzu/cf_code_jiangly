// url:https://codeforces.com/contest/1197/problem/E
// time:2022-04-04 16:44:13
// name:E-CultureCode

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

void merge(ii& cur, ii nxt) {
  if (cur.first > nxt.first) {
    cur = nxt;
  } else if (cur.first == nxt.first) {
    add_mod(cur.second, nxt.second);
  }
}
const int N = 2e5 + 10;
struct Node {
  Node *left, *right;
  ii cnt;
  void pushup() {
    cnt = left->cnt;
    merge(cnt, right->cnt);
  }
};
Node pool[N << 1], *last;
Node* build(int a, int b) {
  Node* ret = last++;
  ret->cnt = {inf<int>, 0};
  if (a + 1 == b) return ret;
  int mid = (a + b) / 2;
  ret->left = build(a, mid);
  ret->right = build(mid, b);
  return ret;
}
void insert(Node* cur, int a, int b, int pos, int key, int val) {
  if (pos < a || pos >= b) return;
  if (a + 1 == b) {
    merge(cur->cnt, ii{key, val});
    return;
  }
  int mid = (a + b) / 2;
  insert(cur->left, a, mid, pos, key, val);
  insert(cur->right, mid, b, pos, key, val);
  cur->pushup();
}
ii query(Node* cur, int a, int b, int ll, int rr) {
  if (ll >= rr || a >= rr || b <= ll) return make_pair(inf<int>, 0);
  if (a >= ll && b <= rr) {
    return cur->cnt;
  }
  int mid = (a + b) / 2;
  ii ret = {inf<int>, 0};
  auto L = query(cur->left, a, mid, ll, rr);
  merge(ret, L);
  auto R = query(cur->right, mid, b, ll, rr);
  merge(ret, R);
  return ret;
}

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
      ckmax(c[x], y);
    }
  }
  T query(int x) {
    T ret = 0;
    for (; x; x -= x & -x) {
      ckmax(ret, c[x]);
    }
    return ret;
  }
};

int main() {
  int n;
  cin >> n;
  vector<array<int, 2>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i][0] >> a[i][1];
  }
  sort(a.begin(), a.end());
  trace(a);

  fenwick F(n);

  last = pool;
  Node* rt = build(0, n);
  vector<ii> dp(n);


  for (int i = 0; i < n; ++i) {
    auto [R, L] = a[i];
    int rr = upper_bound(a.begin(), a.end(), array<int, 2>{{L, inf<int>}}) - a.begin();
    int bound = F.query(rr);
    int ll = upper_bound(a.begin(), a.end(), array<int, 2>{{bound, inf<int>}}) - a.begin();
    trace(ll, rr, bound);
    auto cur = query(rt, 0, n, ll, rr);
    cur.first += L;
    dp[i] = {L, 1};
    merge(dp[i], cur);
    insert(rt, 0, n, i, dp[i].first - R, dp[i].second);
    F.add(i + 1, L);

    trace(L, R, dp[i]);
  }

  int bound = F.query(n);
  int ll = upper_bound(a.begin(), a.end(), array<int, 2>{{bound, inf<int>}}) - a.begin();

  int best = inf<int>, ret = 0;
  for (int i = ll; i < n; ++i) {
    ckmin(best, dp[i].first);
  }
  for (int i = ll; i < n; ++i) {
    if (best == dp[i].first) add_mod(ret, dp[i].second);
  }
  cout << ret << '\n';
  return 0;
}

