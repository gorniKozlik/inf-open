//#pragma GCC optimize("O3", "unroll-loops")

#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>

//#pragma GCC target("avx2")

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

ll crd[N];
ll pt = 0;

pii<2> arr[N];

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

  if (n % 2) {
    while (q--) {
      ll t;
      cin >> t;
      cout << t / 2 << ' ';
    }
  }
  else {
    while (q--) {
      ll t;
      cin >> t;
      cout << t / 2 << ' ';
    }
  }
}

int main() {
  ll t = 1;
  //cin >> t;
  while (t--) solve();

  return 0;
}