// url:https://codeforces.com/contest/1146/problem/E
// time:2022-03-15 15:27:33
// name:E-HotisCold

#define LOCAL
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

const int N = 2e5 + 10;
struct Node {
  Node *left, *right;
  bool rev;
  int c;
  void reverse() {
    c = -c;
    rev ^= 1;
  }
  void assign(int x) {
    c = x;
  }
  void pushdown() {
    if (rev) {
      left->reverse();
      right->reverse();
      rev = 0;
    }
    if (c) {
      left->assign(c);
      right->assign(c);
      c = 0;
    }
  }
};
Node pool[N << 1], *last;
Node* build(int a, int b) {
  Node* ret = last++;
  ret->rev = ret->c = 0;
  if (a + 1 == b) return ret;
  int mid = (a + b) / 2;
  ret->left = build(a, mid);
  ret->right = build(mid, b);
  return ret;
}
void assign(Node* cur, int a, int b, int ll, int rr, int x) {
  if (ll >= rr || a >= rr || b <= ll) return;
  if (a >= ll && b <= rr) {
    cur->assign(x);
    return;
  }
  cur->pushdown();
  int mid = (a + b) / 2;
  assign(cur->left, a, mid, ll, rr, x);
  assign(cur->right, mid, b, ll, rr, x);
}
void reverse(Node* cur, int a, int b, int ll, int rr) {
  if (ll >= rr || a >= rr || b <= ll) return;
  if (a >= ll && b <= rr) {
    cur->reverse();
    return;
  }
  cur->pushdown();
  int mid = (a + b) / 2;
  reverse(cur->left, a, mid, ll, rr);
  reverse(cur->right, mid, b, ll, rr);
}
int get(Node* cur, int a, int b, int pos) {
  if (a + 1 == b) {
    return cur->c;
  }
  cur->pushdown();
  int mid = (a + b) / 2;
  return pos < mid ? get(cur->left, a, mid, pos)
    : get(cur->right, mid, b, pos);
}

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];

  int offassign = 100000;
  last = pool;
  Node* rt = build(0, N);
  assign(rt, 0, N, 0, N, 1);

  while (q--) {
    string op;
    int x;
    cin >> op >> x;
    if (op == ">") {
      if (x >= 0) {
        assign(rt, 0, N, offassign + x + 1, N, -1);
        assign(rt, 0, N, 0, offassign - x, 1);
      } else {
        reverse(rt, 0, N, offassign + x + 1, offassign - x);
        assign(rt, 0, N, offassign - x, N, -1);
        assign(rt, 0, N, 0, offassign + x + 1, 1);
      }
    } else {
      if (x <= 0) {
        assign(rt, 0, N, 0, offassign + x, -1);
        assign(rt, 0, N, offassign - x + 1, N, 1);
      } else {
        reverse(rt, 0, N, offassign - x + 1, offassign + x);
        assign(rt, 0, N, offassign + x, N, 1);
        assign(rt, 0, N, 0, offassign - x + 1, -1);
      }
    }
  }
  vector<int> ret(n);
  for (int i = 0; i < n; ++i) {
    int sign = get(rt, 0, N, offassign + a[i]);
    ret[i] = sign * a[i];
  }
  out(ret);

  return 0;
}

