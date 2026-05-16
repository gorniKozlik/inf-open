#include <bits/stdc++.h>
using ll = long long;
using namespace std;
#define all(a) a.begin(), a.end()

void solve();

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll t = 1;
#ifdef LOCAL
    cin >> t;
#else
#endif
    while (t--) solve();
}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> f(n * 2), l(n), r(n), x;
    for (ll i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        x.push_back(l[i]);
        x.push_back(r[i]);
    }
    sort(all(x));
    for (ll i = 0; i < n; i++) {
        l[i] = lower_bound(all(x), l[i]) - x.begin();
        r[i] = lower_bound(all(x), r[i]) - x.begin();
        f[l[i]] = 1;
        f[r[i]] = -1;
    }
    ll cls = 0, opn = 0;
    vector<vector<ll> > ad(n + 5);
    vector<vector<ll> > dl(n + 5);
    for (ll i = 0; i < 2 * n; i++) {
        ll k = opn + (f[i] == 1);
        ll crs = (n - opn - cls - (f[i] == 1));
        ad[k].push_back(0 - k / 2);
        dl[k + min(cls, crs) * 2 + 2].push_back(0 - k / 2);
        if (crs > cls && f[i] == -1 || crs < cls && f[i] == 1) {
            ll zp = k + min(cls, crs) * 2 + 1;
            ll op = min(cls, crs) + 1;
            ad[zp].push_back(op - zp / 2);
            dl[zp + 2].push_back(op - zp / 2);
        }
        if (f[i] == 1) ++opn;
        else --opn, ++cls;
    }
    vector<ll> ans(n + 1);
    multiset<ll> st[2];
    for (ll i = 0; i <= n; i++) {
        for (ll j: ad[i])
            st[i % 2].insert(j);
        for (ll j: dl[i])
            st[i % 2].erase(st[i % 2].find(j));
        if (!st[i % 2].empty())
            ans[i] = i / 2 + *st[i % 2].begin();
    }
    for (ll i = n - 1; i >= 0; i--)
        ans[i] = min(ans[i], ans[i + 1]);
    while (q--) {
        ll m;
        cin >> m;
        cout << ans[m] << " ";
    }
    cout << "\n";
}
