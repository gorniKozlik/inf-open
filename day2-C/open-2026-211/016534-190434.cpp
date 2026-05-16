#pragma GCC optimize("O3", "unroll-loops")

#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC target("avx2")

using namespace std;
//using namespace __gnu_pbds;

using ll = long long;
template <int N, class T = ll>
using pii = array<T, N>;
//using oset = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;

#ifdef LOCAL
ifstream iss32("in.txt");
#define cin iss32
#endif

constexpr ll N = 2e5 + 15;

ll crd[N * 2];
ll pt = 0;

pii<2> arr[N];
ll ans[N];

ll ind[N * 8];
void solve() {
  ll n, q;
  cin >> n >> q;
  for (ll i = 0; i < n; ++i) cin >> arr[i][0] >> arr[i][1];

  for (ll i = 0; i < n; ++i) {
    crd[pt++] = arr[i][0];
    crd[pt++] = arr[i][1];
  }

  sort(crd, crd + pt);
  {
    ll p = 1;
    for (ll i = 1; i < pt; ++i) {
      if (crd[i] != crd[p - 1]) crd[p++] = crd[i];
    }
    pt = p;

    for (ll i = 0; i < n; ++i) {
      arr[i][0] = lower_bound(crd, crd + pt, arr[i][0]) - crd;
      arr[i][1] = lower_bound(crd, crd + pt, arr[i][1]) - crd;
    }
  }

  set<pii<2>> st;
  for (ll i = 0; i < n; ++i) {
    st.insert({ arr[i][0], 0 });
    st.insert({ arr[i][1], 1 });
  }

  ll cnt = 0;
  ll cur = 0;

  ll mx = 0;
  set<pii<3>> ot;//pos, 0/1, i
  for (ll i = 0; i < 2 * n; ++i) {
    while (st.size() && (*st.begin())[0] == i && (*st.begin())[1] == 0) {
      auto t = *st.begin();
      st.erase(t);
      ++cur;
    }

    mx = max(mx, cur);
    ot.insert({ cur, 0ll, i });
    ind[i] = -cur;
    ot.insert({ cur + 2 * min(cnt, n - cur - cnt), 1ll, i });

    while (st.size() && (*st.begin())[0] == i && (*st.begin())[1] == 1) {
      auto t = *st.begin();
      st.erase(t);

      ++cnt;
      --cur;
    }

    ot.insert({ cur, 0ll, 2 * n + i });
    ind[2 * n + i] = -cur;
    ot.insert({ cur + 2 * min(cnt, n - cur - cnt), 1ll, 2 * n + i });
  }

  set<pii<2>> tmp;
  for (ll i = 0; i <= n; ++i) {
    while (ot.size() && (*ot.begin())[0] == i && (*ot.begin())[1] == 0) {
      auto t = *ot.begin();
      ot.erase(t);

      tmp.insert({ -t[0], t[2] });
    }

    if (i > mx) {
      //while (tmp.size() == 0) cerr << "dfnie" << endl;
      ll mn = -(*tmp.begin())[0];
      //cerr << i << ' ' << mn << endl;
      ans[i] = (i - mn + 1) / 2;
    }

    while (ot.size() && (*ot.begin())[0] == i && (*ot.begin())[1] == 1) {
      auto t = *ot.begin();
      ot.erase(t);

      tmp.erase({ ind[t[2]], t[2] });
    }
  }

  for (ll i = 0; i <= mx; ++i) ans[i] = 0;

  while (q--) {
    ll t;
    cin >> t;
    cout << ans[t] << ' ';
  }
}

int main() {
  ll t = 1;
  //cin >> t;
  while (t--) solve();

  return 0;
}