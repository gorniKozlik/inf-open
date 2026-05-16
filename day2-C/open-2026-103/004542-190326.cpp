#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
using vl = __int128_t;
using ld = long double;
using ul = unsigned long long;
using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define sz(a) (ll)a.size()
const ll mod = 998244353;
ll pw(ll a, ll b) {
    ll r = 1;
    while (b) {
        if (b & 1) r = (r * a) % mod;
        a = (a * a) % mod, b >>= 1;
    }
    return r;
}
// pair<ll, ll> f(ll x, ll k, vector<pair<ll, ll>>& a) {
//     ll lt = 0, rt = 0, pr = 0;
//     for (auto [l, r] : a) {
//         if (r < x) lt++;
//         else if (l > x) rt++;
//         else pr++;
//     }
//     if (k < pr) return {0, pr};
//     if (min(lt, rt) * 2 + pr >= k) return {(k + 1 - pr) / 2, pr};
//     return {max(lt, rt), pr};
// }
void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> a(n);
    vector<array<ll, 3>> ev;
    ll j = 0;
    for (auto& [l, r] : a) {
        cin >> l >> r;
        ev.push_back({l, -1, j});
        ev.push_back({r, 1, j + n});
        j++;
    }    
    sort(all(ev));
    vector<array<ll, 3>> xyz(2 * n);
    ll c = 0, cr = 0, mxz = 0, mxmi = 0, mimx = 1e18;
    for (auto [x, f, id] : ev) {
        if (f == -1) {
            c++;
            xyz[id][0] = cr;
            xyz[id][1] = n - c - cr;
            xyz[id][2] = c;
            mxz = max(mxz, c);
            mxmi = max(mxmi, min(xyz[id][0], xyz[id][1]));
            mimx = min(mimx, max(xyz[id][0], xyz[id][1]));
            //cout << x << ' ' << xyz[id][0] << ' ' << xyz[id][1] << ' ' << xyz[id][2] << '\n';
        } else {
            xyz[id][0] = cr;
            xyz[id][1] = n - c - cr;
            xyz[id][2] = c;
            mxz = max(mxz, c);
            mxmi = max(mxmi, min(xyz[id][0], xyz[id][1]));
            mimx = min(mimx, max(xyz[id][0], xyz[id][1]));
            //cout << x << ' ' << xyz[id][0] << ' ' << xyz[id][1] << ' ' << xyz[id][2] << '\n';
            cr++;
            c--;
        }
    }
    vector<pair<ll, pair<ll, ll>>> pp(n);
    for (ll i = 0; i < n; i++) {
        pp[i].first = min(xyz[i][0], xyz[i][1]) * 2 + xyz[i][2];
        pp[i].second.first = xyz[i][2];
        pp[i].second.second = max(xyz[i][0], xyz[i][1]);
    }
    sort(all(pp));
    vector<ll> sf(n + 1, -1e18), pr(n + 1, 1e18);
    for (ll i = n - 1; i > -1; i--) {
        sf[i] = max(sf[i + 1], pp[i].second.first);
    }
    for (ll i = 0; i < n; i++) pr[i + 1] = min(pr[i], pp[i].second.second);
    while (q--) {
        ll k;
        cin >> k;
        if (k <= mxz) {
            cout << 0 << ' ';
            continue;
        }
        ll ans = 1e18;
        pair<ll, pair<ll, ll>> cr = {k, {(ll)-1e18, (ll)-1e18}};
        ll i = lower_bound(all(pp), cr) - pp.begin();
        if (i != sz(pp)) ans = (k + 1 - sf[i]) / 2;
        i--;
        if (i > -1 && pp[i].first < k) ans = min(ans, pr[i + 1]);
        cout << ans << ' ';
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
