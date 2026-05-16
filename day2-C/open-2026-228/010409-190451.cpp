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
  int l, r, ind;
};

bool cmp_left(const seg& u, const seg& v) {
  return u.l < v.l;
}

bool cmp_right(const seg& u, const seg& v) {
  return u.r > v.r;
}

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
  vector<node> t;

  segtree(int _n) {
    n = _n;
    t.assign(n << 2, {});
  }

  void apply(int x, int v) {
    t[x].add += v;
    t[x].mx += v;
  }

  void push(int x) {
    if (t[x].add != 0) {
      apply(x << 1, t[x].add);
      apply(x << 1 | 1, t[x].add);
      t[x].add = 0;
    }
  }

  void add(int lq, int rq, int v) {
    add(lq, rq, v, 1, 0, n);
  }

  void add(int lq, int rq, int v, int x, int lx, int rx) {
    if (rx <= lq || lx >= rq) {
      return;
    }
    if (lq <= lx && rx <= rq) {
      apply(x, v);
      return;
    }
    push(x);
    int m = lx + rx >> 1;
    add(lq, rq, v, x << 1, lx, m);
    add(lq, rq, v, x << 1 | 1, m, rx);
    t[x] = t[x << 1] + t[x << 1 | 1];
  }

  int get(int lq, int rq) {
    return get(lq, rq, 1, 0, n);
  }

  int get(int lq, int rq, int x, int lx, int rx) {
    if (rx <= lq || lx >= rq) {
      return node().mx;
    }
    if (lq <= lx && rx <= rq) {
      return t[x].mx;
    }
    push(x);
    int m = lx + rx >> 1;
    int lval = get(lq, rq, x << 1, lx, m);
    int rval = get(lq, rq, x << 1 | 1, m, rx);
    t[x] = t[x << 1] + t[x << 1 | 1];
    return max(lval, rval);
  }
};

constexpr int kInf = 1e9 + 10;

void compute(int test_case) {
  int n, q;
  cin >> n >> q;
  vector<seg> a(n);
  vector<int> c;
  for (int i = 0; i < n; ++i) {
    cin >> a[i].l >> a[i].r;
    a[i].ind = i;
    c.push_back(a[i].l);
    c.push_back(a[i].r);
  }
  sort(all(c));
  reuniq(c);
  for (auto& [l, r, i] : a) {
    l = lower_bound(all(c), l) - c.begin();
    r = lower_bound(all(c), r) - c.begin();
  }
  sort(all(a), cmp_left);
  auto b = a;
  sort(all(b), cmp_right);
  segtree st(2 * n);
  for (auto [l, r, i] : a) {
    st.add(l, r + 1, 1);
  }
  vector<int> ans(n + 1, kInf);
  ans[st.get(0, 2 * n)] = 0;
  vector<bool> use(n, false);
  int ptr = 0;
  for (int i = 0; i < n; ++i) {
    if (use[a[i].ind]) {
      continue;
    }
    use[a[i].ind] = 1;
    while (ptr < n && use[b[ptr].ind]) {
      ++ptr;
    }
    if (ptr == n) {
      break;
    }
    use[b[ptr].ind] = 1;
    auto [l, r, _] = a[i];
    auto [l2, r2, __] = b[ptr];
    st.add(l, r + 1, -1);
    st.add(l2, r2 + 1, -1);
    st.add(l, l2 + 1, 1);
    st.add(r, r2 + 1, 1);
    remin(ans[st.get(0, 2 * n)], i + 1);
  }
  for (int i = n - 1; i >= 0; --i) {
    remin(ans[i], ans[i + 1]);
  }
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