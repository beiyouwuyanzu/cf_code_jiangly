// url:https://codeforces.com/contest/1660/problem/F2
// time:2022-03-31 19:09:24
// name:F2-PromisingString(hardversion)

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
int c[N];

void add(int x, int y) {
  if (x <= 0) return;
  for (; x < N; x += x & -x) {
    c[x] += y;
  }
}
int query(int x) {
  int ret = 0;
  for (; x; x -= x & -x) {
    ret += c[x];
  }
  return ret;
}

struct Query {
  int x, y;
  int type; // 0: add, 1: positive query;
};

int64 ret;
void solve2(const vector<Query>& b, int L, int R) {
  for (auto& [x, y, type] : b) {
    if (type == 0) {
      add(y, 1);
    } else {
      ret += query(y);
    }
  }
  for (auto& [x, y, type] : b) {
    if (type == 0) add(y, -1);
  }
}

void solve1(const vector<Query>& a, int L, int R) {
  if (R - L <= 1) return;
  int mid = (L + R) / 2;
  solve1(a, L, mid);
  solve1(a, mid, R);
  vector<Query> b;
  for (int i = L; i < mid; ++i) {
    if (a[i].type == 0) b.push_back(a[i]);
  }
  for (int i = mid; i < R; ++i) {
    if (a[i].type != 0) b.push_back(a[i]);
  }
  sort(b.begin(), b.end(),
       [&](const auto& L, const auto& R) {
         return L.x < R.x || (L.x == R.x && L.type < R.type);
       });
  solve2(b, 0, SZ(b));
}

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int n;
    string s;
    cin >> n >> s;
    vector<int> pre(n + 1), A(1, 0);
    for (int i = 0; i < n; ++i) {
      pre[i + 1] = pre[i] + (s[i] == '-' ? 1 : -1);
      A.push_back(pre[i + 1]);
    }
    dedup(A);
    vector<int> sum(n + 1);
    for (int i = 0; i < n; ++i) {
      sum[i + 1] = sum[i];
      if (i > 0 && s[i] == '-' && s[i - 1] == '-') sum[i + 1]++;
    }

    ret = 0;
    for (int k = 0; k < 3; ++k) {
      vector<Query> a;
      for (int i = 0; i <= n; ++i) {
        int r = (pre[i] % 3 + 3) % 3;
        if (r != k) continue;
        int cur = 3 * sum[i] - pre[i];
        int id = lower_bound(A.begin(), A.end(), pre[i]) - A.begin() + 1;

        // trace(k, i, cur, id);
        // pre[j] <= pre[i] && cur[j] <= cur[i];
        a.push_back(Query{cur, id, 1});
        if (i - 1 >= 0 && s[i - 1] == '-' && s[i] == '-') cur += 3;
        a.push_back(Query{cur, id, 0});
      }
      // for (auto [x, y, type] : a) trace(x, y, type);
      // trace("---------_");
      solve1(a, 0, SZ(a));
      // trace(ret);
    }
    cout << ret << '\n';
  }

  return 0;
}

