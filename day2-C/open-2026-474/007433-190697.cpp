#include<bits/stdc++.h>
using namespace std;

#define int long long
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define pb push_back
#define eb emplace_back

const int MOD = 1e9+7;
const int MAXN = 5e5+5;
const int inf = 2e18+5;

struct event {
  int x, t;
};

bool cmp(const event&a, const event&b) {
  if (a.x != b.x) return a.x < b.x;
  return a.t > b.t;
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q; cin >> n >> q;
  vector<event> a;
  for (int i = 0; i < n; i++) {
    int l, r; cin >> l >> r;
    a.pb({l, 1});
    a.pb({r, -1});
  }
  sort(all(a), cmp);

  int cur = 0, le = 0, ri = n;
  vector<int> best(n+1);
  for (auto [x, t]: a) {
    if (t == 1) {
      cur++;
      ri--;
    }
    int dif = abs(le-ri);
    best[dif] = max(best[dif], cur);
    if (t == -1) {
      cur--;
      le++;
    }
    dif = abs(le-ri);
    best[dif] = max(best[dif], cur);
  }

  for (int i = 1; i <= n; i++) best[i] = max(best[i], best[i-1]);
  while (q--) {
    int k; cin >> k;
    // abs(le-ri) <= n-k
    int be = best[n-k];
    if (be >= k) {
      cout << 0 << ' ';
      continue;
    }
    int extra = (k-be+1)/2;
    cout << extra << ' ';
  }
}