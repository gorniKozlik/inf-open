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

void solve() {
  cin >> n >> q;
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
      for (int d = 0; d <= D; ++d) {
        assert(cnt_self + d * 2 <= n);
        ans[cnt_self + d * 2] = min(ans[cnt_self + d * 2], d);
        if (r) {
          ans[cnt_self + d * 2 + 1] = min(ans[cnt_self + d * 2 + 1], d + 1);
        }
      }
    }
  }
  for (int qq = 0; qq < q; ++qq) {
    int k;
    cin >> k;
    cout << ans[k] << ' ';
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