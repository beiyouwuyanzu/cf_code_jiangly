// url:https://codeforces.com/contest/1364/problem/D
// time:2021-11-15 16:29:57
// name:D-Ehab'sLastCorollary

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

const int N = 1e5 + 10;
vector<int> a[N];
int dep[N], pre[N];
int minLen;
vector<int> c;

void DFS(int u, int parent) {
  dep[u] = parent < 0 ? 0 : dep[parent] + 1;
  for (auto& v : a[u]) {
    if (v == parent) continue;
    if (pre[v] < 0) {
      pre[v] = u;
      DFS(v, u);
    } else {
      // find odd cycle
      if (dep[v] < dep[u] && (dep[u] - dep[v]) % 2 == 0) {
        int len = dep[u] - dep[v] + 1;
        ckmin(minLen, len);
      }
    }
  }
}

bool DFS2(int u, int parent) {
  for (auto& v : a[u]) {
    if (v == parent) continue;
    if (pre[v] < 0) {
      pre[v] = u;
      if (DFS2(v, u)) return true;
    } else {
      if (dep[v] < dep[u] && dep[u] - dep[v] + 1 == minLen) {
        for (int t = u; t != v; t = pre[t]) c.push_back(t + 1);
        c.push_back(v + 1);
        return true;
      }
    }
  }
  return false;
}

int main() {
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    --x; --y;
    a[x].push_back(y);
    a[y].push_back(x);
  }
  fill(pre, pre + n, -1);
  pre[0] = 0;
  minLen = inf<int>;
  DFS(0, -1);
  trace(minLen);

  if (minLen == inf<int>) {
    cout << 1 << '\n';
    vector<vector<int>> can(2);
    for (int i = 0; i < n; ++i) {
      int x = dep[i] % 2;
      can[x].push_back(i + 1);
    }
    for (int x = 0; x < 2; ++x) {
      if (SZ(can[x]) >= (k + 1) / 2) {
        can[x].resize((k + 1) / 2);
        out(can[x]);
        break;
      }
    }
    return 0;
  }

  fill(pre, pre + n, -1);
  pre[0] = 0;
  DFS2(0, -1);

  if (SZ(c) <= k) {
    cout << 2 << '\n';
    cout << SZ(c) << '\n';
    out(c);
  } else {
    vector<int> ret;
    for (int i = 0; i < SZ(c); i += 2) ret.push_back(c[i]);
    ret.resize((k + 1) / 2);
    cout << 1 << '\n';
    out(ret);
  }
  return 0;
}

