// url:https://codeforces.com/contest/1370/problem/F1
// time:2021-11-15 15:01:58
// name:F1-TheHiddenPair(EasyVersion)

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

const int N = 1e3 + 10;
vector<int> a[N];

array<int, 2> query(const vector<int>& c) {
  cout << "? " << SZ(c);
  for (auto& x : c) {
    cout << " " << x + 1;
  }
  cout << endl;
  array<int, 2> ret;
  cin >> ret[0] >> ret[1];
  return ret;
}

int dep[N];
void dfs(int u, int parent, int depth) {
  dep[u] = depth;
  for (auto& v : a[u]) {
    if (v == parent) continue;
    dfs(v, u, depth + 1);
  }
}

int main() {
  int cas;
  cin >> cas;
  while (cas--) {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) a[i].clear();
    for (int i = 0; i < n - 1; ++i) {
      int x, y;
      cin >> x >> y;
      --x; --y;
      a[x].push_back(y);
      a[y].push_back(x);
    }
    vector<int> cur(n);
    iota(cur.begin(), cur.end(), 0);
    auto ret = query(cur);
    int r = ret[0] - 1, D = ret[1];
    dfs(r, -1, 0);

    int max_dep = *max_element(dep, dep + n);
    vector<vector<int>> lev(max_dep + 1);
    for (int i = 0; i < n; ++i) {
      lev[dep[i]].push_back(i);
    }
    int low = 1, high = max_dep;
    while (low != high) {
      int mid = (low + high + 1) / 2;
      auto ret = query(lev[mid]);
      if (ret[1] != D) {
        high = mid - 1;
      } else {
        low = mid;
      }
    }
    ret = query(lev[high]);
    int u = ret[0] - 1;
    dfs(u, -1, 0);

    cur.clear();
    for (int i = 0; i < n; ++i) {
      if (dep[i] == D) cur.push_back(i);
    }
    ret = query(cur);
    int v = ret[0] - 1;
    cout << "! " << u + 1 << " " << v + 1 << endl;
    string verify;
    cin >> verify;
    if (verify == "Incorrect") return 0;
  }
  return 0;
}

