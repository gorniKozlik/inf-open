#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve();

signed main() {
    solve();
}

struct zxc {
    ll x;
    ll fl;
};

bool cmp(zxc a, zxc b) {
    return a.x < b.x || (a.x == b.x && a.fl > b.fl);
}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<zxc> v;
    vector<ll> ls(n), rs(n);
    for (ll i = 0; i < n; i++) {
        cin >> ls[i] >> rs[i];
        v.emplace_back(ls[i], 1);
        v.emplace_back(rs[i], -1);
    }
    sort(ls.begin(), ls.end());
    sort(rs.begin(), rs.end());
    sort(v.begin(), v.end(), cmp);
    if (n * n * 30 < n * q) {
        vector<ll> ans(n + 1, 1e9);
        ll cnt = 0;
        for (ll i = 0; i < 2 * n; i++) {
            ll l1 = -1, r1 = n, l2 = -1, r2 = n;
            while (r1 - l1 > 1) {
                ll m = (r1 + l1) / 2;
                if (rs[m] >= v[i].x) r1 = m;
                else l1 = m;
            }
            while (r2 - l2 > 1) {
                ll m = (r2 + l2) / 2;
                if (ls[m] > v[i].x) r2 = m;
                else l2 = m;
            }
            ll x = min(n - r2, r1);
            for (ll j = 0; j <= n; j++) {
                ll e = j - cnt;
                if (x * 2 >= e) ans[j] = min(ans[j], (e + 1) / 2);
                else ans[j] = min(ans[j], e - x);
            }
            cnt += v[i].fl;
        }
        while (q--) {
            ll k;
            cin >> k;
            ll o = 0;
            cout << max(ans[k], o) << ' ';
        }
        return;
    }
    while (q--) {
        ll k;
        cin >> k;
        ll mx = 1e9, cnt = 0;
        for (ll i = 0; i < 2 * n; i++) {
            ll l1 = -1, r1 = n, l2 = -1, r2 = n;
            while (r1 - l1 > 1) {
                ll m = (r1 + l1) / 2;
                if (rs[m] >= v[i].x) r1 = m;
                else l1 = m;
            }
            while (r2 - l2 > 1) {
                ll m = (r2 + l2) / 2;
                if (ls[m] > v[i].x) r2 = m;
                else l2 = m;
            }
            ll x = min(n - r2, r1);
            ll e = k - cnt;
            if (x * 2 >= e) mx = min(mx, (e + 1) / 2);
            else mx = min(mx, e - x);
            cnt += v[i].fl;
        }
        ll o = 0;
        cout << max(mx, o) << ' ';
    }
}
