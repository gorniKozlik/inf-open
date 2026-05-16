#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
using ll = long long;
using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
const ll maxn = 1e6 + 5;
const ll MOD = 998244353;
const ll INF = 3e18;

ll mmod(ll x, ll mod = MOD) {
    x = x%MOD;
    if (x < 0) {
        x += MOD;
    }
    return x;
}

ll binpow(ll a, ll n) {
    ll res = 1;
    while (n > 0) {
        if (n&1) {
            res= res*a % MOD;
        }
        a = a*a%MOD;
        n >>=1;
    }
    return res;

}


void solve() {
    ll n, q;
    cin >> n >> q;
    vector<array<ll,3>> ev;
    vector<ll> lf;
    vector<ll> rt;
    for (int i = 0; i < n; ++i) {
        ll l, r;
        cin >> l >> r;
        ev.push_back({l, 0, i});
        ev.push_back({r, 1, i});
        lf.push_back(l);
        rt.push_back(r);
    }
    sort(ev.begin(), ev.end());
    sort(lf.begin(), lf.end());
    sort(rt.begin(), rt.end());
    ll cnt = 0;
    ll curl = 0;
    ll f = 0;
    vector<ll> op(n+1);
    ll numop = 1;
    vector<vector<ll>> cl(n+1);
    op[0]++;
    if (n % 2 == 0) {
        cl[n].push_back(0);
    } else {
        cl[n-1].push_back(0);
    }
    for (int i = 0; i < ev.size(); ++i) {
        if (ev[i][1] == 0) {
            curl = ev[i][0];
            f = 1;
            cnt++;
        } else {
            if (f == 0) {
                cnt--;
            } else {
                f = 0;
                ll cntl = lower_bound(rt.begin(), rt.end(), curl) - rt.begin();
                ll cntr = lf.end() - upper_bound(lf.begin(), lf.end(), ev[i][0]);
                ll mih = min(cntl, cntr);
                op[cnt]++;
                numop++;
                cl[cnt + mih*2].push_back(cnt);
                cnt--;
            }
        }

    }
    vector<ll> ans(n+1);
    ll cntop = 0;
    ll maxl = -1;
    ll bal = 0;
    multiset<ll> s;
    ll valclose = INF;
    for (int i = 0; i <= n; ++i) {
      if (cntop < numop) {
          ans[i] = 0;
      } else {
          ll res = INF;
          if (s.size() != 0) {
              ll v = *(--s.end());
              res = min(res, (i-v)/2 + (i-v)%2);
          }
          res = min(res, valclose);
          ans[i] = res;
      }
        for (int j = 0; j < op[i]; ++j) {
            s.insert(i);
            cntop++;
        }
        for (auto e : cl[i]) {
            ll v  = (i - e)/2;
            valclose = min(valclose, v);
            s.erase(s.find(e));
        }
        valclose++;
    }
    for (int i = 0; i < q; ++i) {
        ll c;
        cin >> c;
        cout << ans[c] << " ";
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifdef LOCAL
    freopen("C:\\work\\untitled1\\in.txt", "r", stdin);
    freopen("C:\\work\\untitled1\\out.txt", "w", stdout);
#endif
    int tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
        cout << '\n';
    }
}