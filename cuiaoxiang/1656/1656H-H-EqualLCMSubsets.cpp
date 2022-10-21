// url:https://codeforces.com/contest/1656/problem/H
// time:2022-04-05 15:03:46
// name:H-EqualLCMSubsets

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

template <size_t N>
struct segtree {
  struct Node {
    Node *left, *right;
    int128 val;
    void pushup() {
      val = __gcd(left->val, right->val);
    }
  };
  Node pool[N << 1];
  Node* rt;
  Node* last;
  int n;
  void init(int n) {
    this->n = n;
    last = pool;
    rt = build(0, n);
  }
  void insert(int pos, int128 val) {
    insert(rt, 0, n, pos, val);
  }
  int128 query(int ll, int rr) {
    return query(rt, 0, n, ll, rr);
  }
  Node* build(int a, int b) {
    Node* ret = last++;
    ret->val = 0;
    if (a + 1 == b) return ret;
    int mid = (a + b) / 2;
    ret->left = build(a, mid);
    ret->right = build(mid, b);
    return ret;
  }
  void insert(Node* cur, int a, int b, int pos, int128 val) {
    if (pos < a || pos >= b) return;
    if (a + 1 == b) {
      cur->val = val;
      return;
    }
    int mid = (a + b) / 2;
    insert(cur->left, a, mid, pos, val);
    insert(cur->right, mid, b, pos, val);
    cur->pushup();
  }
  int128 query(Node* cur, int a, int b, int ll, int rr) {
    if (ll >= rr || a >= rr || b <= ll) return 0;
    if (a >= ll && b <= rr) {
      return cur->val;
    }
    int mid = (a + b) / 2;
    int128 ret = 0;
    ret = __gcd(ret, query(cur->left, a, mid, ll, rr));
    ret = __gcd(ret, query(cur->right, mid, b, ll, rr));
    return ret;
  }
};

const int N = 1e3 + 10;
segtree<N> A[N], B[N];

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int n, m;
    cin >> n >> m;
    // trace(cas, n, m);
    vector<int128> a(n), b(m);
    auto read =
      [&]() {
        int128 ret = 0;
        string s;
        cin >> s;
        for (auto& c : s) ret = ret * 10 + (c - '0');
        return ret;
      };
    auto print =
      [&](int128 x) {
        vector<int> digit;
        for (int128 t = x; t; t /= 10) digit.push_back(t % 10);
        reverse(digit.begin(), digit.end());
        for (auto& x : digit) cout << x;
      };
    for (int i = 0; i < n; ++i) a[i] = read();
    for (int i = 0; i < m; ++i) b[i] = read();

    // trace(n, m);
    // for (int i = 0; i < n; ++i) print(a[i]), cout << " "; cout << endl;
    // for (int i = 0; i < m; ++i) print(b[i]), cout << " "; cout << endl;

    // vector<segtree<N>> A, B;
    for (int i = 0; i < n; ++i) {
      // A.push_back(segtree<N>(m));
      A[i].init(m);
      for (int j = 0; j < m; ++j) {
        A[i].insert(j, a[i] / __gcd(a[i], b[j]));
      }
    }
    for (int j = 0; j < m; ++j) {
      B[j].init(n);
      for (int i = 0; i < n; ++i) {
        B[j].insert(i, b[j] / __gcd(b[j], a[i]));
      }
    }

    set<int> canA, canB;
    for (int i = 0; i < n; ++i) canA.insert(i);
    for (int i = 0; i < m; ++i) canB.insert(i);
    while (SZ(canA) && SZ(canB)) {
      trace(canA, canB);
      int k = -1;
      for (auto& i : canA) {
        if (A[i].query(0, m) > 1) {
          k = i;
          break;
        }
      }
      trace("try A", k);
      if (k != -1) {
        canA.erase(k);
        for (auto& j : canB) {
          B[j].insert(k, 0);
        }
        continue;
      }
      k = -1;
      for (auto& j : canB) {
        if (B[j].query(0, n) > 1) {
          k = j;
          break;
        }
      }
      trace("try B", k);
      if (k != -1) {
        canB.erase(k);
        for (auto& i : canA) {
          A[i].insert(k, 0);
        }
        continue;
      }
      break;
    }
    if (SZ(canA) && SZ(canB)) {
      cout << "YES" << '\n';
      cout << SZ(canA) << " " << SZ(canB) << '\n';
      bool first = 1;
      for (auto& i : canA) {
        if (first) {
          first = 0;
        } else {
          cout << " ";
        }
        print(a[i]);
      }
      cout << '\n';
      first = 1;
      for (auto& j : canB) {
        if (first) {
          first = 0;
        } else {
          cout << " ";
        }
        print(b[j]);
      }
      cout << '\n';
    } else {
      cout << "NO" << '\n';
    }
  }

  return 0;
}

