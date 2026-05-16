// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;

#define all(x) x.begin(), x.end()
// #define int long long
using ld = long double;
using ll = long long;
using pii = pair<int, int>;

enum class ET { OPEN = 0, POINT = 1, CLOSE = 2 };

struct Event {
  int coord;
  ET type;
};

bool operator<(const Event& a, const Event& b) {
  if (a.coord != b.coord) return a.coord < b.coord;
  return a.type < b.type;
}

int n, q;
vector<Event> events;

struct Tree {
  vector<int> tree, delta;
  void build() {
    tree.resize((n + 1) * 4, -1);
    delta.resize((n + 1) * 4, -1);
  }
  void push(int v, int l, int r) {
    if (delta[v] == -1) return;
    tree[v] = max(tree[v], delta[v]);
    if (l != r - 1) {
      delta[v * 2 + 1] = max(delta[v * 2 + 1], delta[v]);
      delta[v * 2 + 2] = max(delta[v * 2 + 2], delta[v]);
    }
    delta[v] = -1;
  }
  void mod(int v, int l, int r, int L, int R, int x) {
    push(v, l, r);
    if (R <= l || r <= L) return;
    if (L <= l && r <= R) {
      delta[v] = x;
      push(v, l, r);
      return;
    }
    int m = (l + r) / 2;
    mod(v * 2 + 1, l, m, L, R, x);
    mod(v * 2 + 2, m, r, L, R, x);
    tree[v] = max(tree[v * 2 + 1], tree[v * 2 + 2]);
  }
  void mod(int L, int R, int x) { mod(0, 0, n + 1, L, R + 1, x); }
  int get(int v, int l, int r, int i) {
    push(v, l, r);
    if (l == r - 1) {
      assert(l == i);
      return tree[v];
    }
    int m = (l + r) / 2;
    if (i < m) {
      return get(v * 2 + 1, l, m, i);
    } else {
      return get(v * 2 + 2, m, r, i);
    }
  }
  int get(int i) { return get(0, 0, n + 1, i); }
};

void solve() {
  cin >> n >> q;
  Tree teven, todd;
  teven.build();
  todd.build();

  events.reserve(n * 4);
  for (int i = 0; i < n; ++i) {
    int l, r;
    cin >> l >> r;
    events.push_back({l, ET::OPEN});
    events.push_back({l, ET::POINT});
    events.push_back({r, ET::POINT});
    events.push_back({r, ET::CLOSE});
  }
  sort(all(events));
  vector<int> ans(n + 1, INT_MAX);
  int cnt_closed = 0;
  int cnt_open = 0;
  for (const auto& e : events) {
    if (e.type == ET::OPEN) {
      ++cnt_open;
    } else if (e.type == ET::CLOSE) {
      --cnt_open;
      ++cnt_closed;
    } else if (e.type == ET::POINT) {
      int cnt_self = cnt_open;
      int cnt_left = cnt_closed;
      int cnt_right = n - cnt_self - cnt_left;
      int D = min(cnt_left, cnt_right);
      bool r = abs(cnt_left - cnt_right) > 0;
      if (cnt_self % 2 == 0) {
        teven.mod(cnt_self, cnt_self + D * 2, cnt_self);
        if (r) {
          todd.mod(cnt_self, cnt_self + D * 2 + 1, cnt_self);
        }
      } else {
        todd.mod(cnt_self, cnt_self + D * 2, cnt_self);
        if (r) {
          teven.mod(cnt_self, cnt_self + D * 2 + 1, cnt_self);
        }
      }
      // for (int d = 0; d <= D; ++d) {
      //   assert(cnt_self + d * 2 <= n);
      //   ans[cnt_self + d * 2] = min(ans[cnt_self + d * 2], d);
      //   if (r) {
      //     ans[cnt_self + d * 2 + 1] = min(ans[cnt_self + d * 2 + 1], d + 1);
      //   }
      // }
    }
  }
  for (int qq = 0; qq < q; ++qq) {
    int k;
    cin >> k;
    int i = todd.get(k);
    int j = teven.get(k);
    int v1 = (k - i + 1) / 2;
    int v2 = (k - j + 1) / 2;
    int val = min(v1, v2);
    cout << val << ' ';
  }
  cout << '\n';
}

signed main() {
  cin.tie(nullptr);
  ios::sync_with_stdio(false);

#ifdef ROMALOCAL
  freopen("in.txt", "r", stdin);
#endif

  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}