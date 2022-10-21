// url:https://codeforces.com/contest/547/problem/E
// time:2022-04-08 04:03:46
// name:E-MikeandFriends

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

template<size_t N, size_t K>
struct PersistentSegtree {
  struct Node {
    Node *left, *right;
    int64 sum;
    void pushup() {
      sum = left->sum + right->sum;
    }
  };

  Node *rt[N];
  Node pool[N * K + (N << 1)], *last;
  int n;

  PersistentSegtree(int n): n(n) {
    last = pool;
    rt[0] = build(0, n);
  }
  Node* build(int a, int b) {
    Node* cur = last++;
    cur->sum = 0;
    if (a + 1 == b) return cur;
    cur->left = build(a, (a + b) / 2);
    cur->right = build((a + b) / 2, b);
    return cur;
  }
  void insert(int pre, int cur, int pos, int64 val) {
    insert(rt[pre], rt[cur], 0, n, pos, val);
  }
  void insert(Node* pre, Node*& cur, int a, int b, int pos, int64 val) {
    if (pos < a || pos >= b) return;
    cur = last++;
    *cur = *pre;
    if (a + 1 == b) {
      cur->sum += val;
      return;
    }
    int mid = (a + b) / 2;
    insert(pre->left, cur->left, a, mid, pos, val);
    insert(pre->right, cur->right, mid, b, pos, val);
    cur->pushup();
  }
  int get(int pre, int cur, int64 k) {
    return get(rt[pre], rt[cur], 0, n, k);
  }
  int get(Node* pre, Node* cur, int a, int b, int64 k) {
    if (a + 1 == b) return a;
    int mid = (a + b) / 2;
    int64 cnt = cur->left->sum - pre->left->sum;
    return (cnt >= k)
      ? get(pre->left, cur->left, a, mid, k)
      : get(pre->right, cur->right, mid, b, k - cnt);
  }
  int64 query(int pre, int cur, int ll, int rr) {
    return query(rt[pre], rt[cur], 0, n, ll, rr);
  }
  int64 query(Node* pre, Node* cur, int a, int b, int ll, int rr) {
    if (ll >= rr || a >= rr || b <= ll) return 0LL;
    if (a >= ll && b <= rr) {
      return cur->sum - pre->sum;
    }
    int mid = (a + b) / 2;
    int64 ret = 0;
    ret += query(pre->left, cur->left, a, mid, ll, rr);
    ret += query(pre->right, cur->right, mid, b, ll, rr);
    return ret;
  }
};

const int N = 2e5 + 10;
const int K = 22;
using psegtree = PersistentSegtree<N, K>;

template<size_t N, size_t SIGMA>
struct AhoCorasickAutomaton {
  struct Node {
    Node* child[SIGMA];
    Node *fail, *parent;
    int tin, tout;
  };
  Node pool[N], *last, *rt;
  AhoCorasickAutomaton() {
    last = pool;
    rt = new_node(nullptr, nullptr);
  }
  Node* new_node(Node* fail, Node* parent) {
    Node* p = last++;
    p->fail = fail;
    p->parent = parent;
    fill(p->child, p->child + SIGMA, (Node*)nullptr);
    return p;
  }
  Node* insert(const string& s) {
    Node* p = rt;
    for (auto& c : s) {
      int k = c - 'a';
      if (!p->child[k]) p->child[k] = new_node(rt, p);
      p = p->child[k];
    }
    return p;
  }
  void build() {
    queue<Node*> Q;
    for (int k = 0; k < SIGMA; ++k) {
      if (rt->child[k]) Q.push(rt->child[k]);
    }
    while (!Q.empty()) {
      Node* p = Q.front();
      Q.pop();
      for (int k = 0; k < SIGMA; ++k) {
        if (!p->child[k]) {
          p->child[k] = p->fail->child[k];
        } else {
          p->child[k]->fail = p->fail->child[k] ? p->fail->child[k] : rt;
          Q.push(p->child[k]);
        }
      }
    }

    // dfs fail tree
    vector<vector<int>> a(last - pool);
    for (Node* p = rt + 1; p != last; ++p) {
      auto q = p->fail;
      int x = q - pool, y = p - pool;
      a[x].push_back(y);
    }
    int stamp = 0;
    function<void(int)> dfs =
      [&](int u) {
        pool[u].tin = stamp++;
        for (auto& v : a[u]) {
          dfs(v);
        }
        pool[u].tout = stamp;
      };
    dfs(0);
  }
};

const int SIGMA = 26;
using acam = AhoCorasickAutomaton<N, SIGMA>;

int main() {
  int n, q;
  cin >> n >> q;
  string s;
  acam tr;

  vector<acam::Node*> pos(n);
  for (int i = 0; i < n; ++i) {
    cin >> s;
    pos[i] = tr.insert(s);
  }
  tr.build();

  psegtree ptr(tr.last - tr.pool);
  for (int i = 0; i < n; ++i) {
    bool first = 1;
    for (acam::Node* p = pos[i]; p; p = p->parent) {
      if (first) {
        ptr.insert(i, i + 1, p->tin, 1);
        first = 0;
      } else {
        ptr.insert(i + 1, i + 1, p->tin, 1);
      }
    }
  }
  while (q--) {
    int L, R, x;
    cin >> L >> R >> x;
    --L; --x;
    int ret = ptr.query(L, R, pos[x]->tin, pos[x]->tout);
    cout << ret << '\n';
  }
  return 0;
}

