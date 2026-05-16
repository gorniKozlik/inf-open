#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) x.begin(), x.end()

template<typename T>
int isz(const T& v) {
  return (int)v.size();
}

template<typename T>
void reuniq(T& v) {
  v.erase(unique(all(v)), v.end());
}

template<typename X, typename Y>
bool remin(X& x, const Y& y) {
  if (y < x) {
    x = y;
    return true;
  }
  return false;
}

template<typename X, typename Y>
bool remax(X& x, const Y& y) {
  if (y > x) {
    x = y;
    return true;
  }
  return false;
}

struct seg {
  int l, r;

  bool operator<(const seg& s) const {
    return l < s.l || l == s.l && r < s.r;
  }
};

struct segtree {
  struct node {
    int mx, add;

    node() : mx(0), add(0) {}

    node operator+(const node& v) const {
      node ans;
      ans.mx = max(mx, v.mx);
      return ans;
    }
  };

  int n;
  // vector<node> t;
  vector<int> t;

  segtree(int _n) {
    n = _n;
    // t.assign(n << 2, {});
    t.assign(n, 0);
  }

  void apply(int x, int v) {

  }

  void push(int x) {

  }

  void add(int lq, int rq, int v) {
    for (int i = lq; i < rq; ++i) {
      t[i] += v;
    }
  }

  void add(int lq, int rq, int v, int x, int lx, int rx) {

  }

  int get(int lq, int rq) {
    int ans = 0;
    for (int i = lq; i < rq; ++i) {
      remax(ans, t[i]);
    }
    return ans;
  }

  int get(int lq, int rq, int x, int lx, int rx) {

  }
};

constexpr int kInf = 1e9 + 10;

void compute(int test_case) {
  int n, q;
  cin >> n >> q;
  vector<seg> a(n);
  vector<int> c;
  for (auto& [l, r] : a) {
    cin >> l >> r;
    c.push_back(l);
    c.push_back(r);
  }
  sort(all(a));
  sort(all(c));
  reuniq(c);
  for (auto& [l, r] : a) {
    l = lower_bound(all(c), l) - c.begin();
    r = lower_bound(all(c), r) - c.begin();
  }
  // segtree st(2 * n);
  // for (auto [l, r] : a) {
  //   st.add(l, r + 1, 1);
  // }
  vector<int> ans(n + 1, kInf);
  // remin(ans[st.get(0, 2 * n)], 0);
  // for (int i = 0, j = n - 1, tt = 1; i < j; ++i, --j, ++tt) {
  //   auto [l, r] = a[i];
  //   auto [l2, r2] = a[j];
  //   st.add(l, r + 1, -1);
  //   st.add(l2, r2 + 1, -1);
  //   st.add(l, l2 + 1, 1);
  //   st.add(r, r2 + 1, 1);
  //   remin(ans[st.get(0, 2 * n)], tt);
  // }
  for (int i = n - 1; i > 0; --i) {
    remin(ans[i], ans[i + 1]);
  }
  iota(all(ans), -1);
  for (int tt = 0; tt < q; ++tt) {
    int k;
    cin >> k;
    cout << ans[k] << " ";
  }
  cout << "\n";
}

signed main() {
  #ifdef LOCAL
    freopen("/home/olymp/work/in.txt", "r", stdin);
    // freopen("/home/olymp/work/out.txt", "w", stdout);
  #endif
  cin.tie(0)->sync_with_stdio(0);
  int t = 1;
  // cin >> t;
  for (int tt = 1; tt <= t; ++tt) {
    compute(tt);
  }
  return 0;
}