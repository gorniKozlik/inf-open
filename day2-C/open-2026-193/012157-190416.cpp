#include<iostream>
#include<algorithm>
#include<set>
#pragma GCC optimize("Ofast")
using namespace std;

using ll = long long;
using ld = long double;

const ll infl = (ll)4e18 + 100;
const ll infi = (ll)1e9 + 100;
const ll maxn = (ll)1e6 + 10;
const ll mod = (ll)1e9 + 7;

ll n, q;
pair<ll, ll> a[maxn];
pair<ll, ll> sl[maxn];
pair<ll, ll> sr[maxn];
ll ans[maxn];
set<pair<ll, ll>> st;
ll qs[maxn];

inline bool cmp(pair<ll, ll> sr1, pair<ll, ll> sr2) {
    if (sr1.second != sr2.second)
        return sr1.second > sr2.second;
    return sr1.first > sr2.first;
}

inline void solve() {
    cin >> n >> q;
    for (ll i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        sl[i] = a[i]; sr[i] = a[i];
        st.insert({ a[i].first, 1 });
        st.insert({ a[i].second, 2 });
    }

    ll mx_qs = -infl;
    for (ll i = 0; i < q; ++i) {
        cin >> qs[i];
        mx_qs = max(mx_qs, qs[i]);
    }

    sort(sl, sl + n);
    sort(sr, sr + n, cmp);

    ll k = 0, mx_k = -1, ps = 1;
    for (auto& p : st) {
        if (p.second == 1)
            ++k;
        else --k;

        if (k > mx_k) {
            mx_k = k;
            ps = p.first;
        }
    }

    ans[0] = -1;
    ll last = 1;

    ll nw = mx_k;
    for (ll j = last; j <= nw; ++j)
        ans[j] = ans[last - 1] + 1;

    last = nw + 1;

    ll l = 0, r = 0;
    for (ll i = 0; i < n; ++i) {
        if (sl[l++].second >= ps) --mx_k;
        if (sr[r++].first <= ps) --mx_k;
        mx_k += 2;

        nw = mx_k;
        for (ll j = last; j <= nw; ++j)
            ans[j] = ans[last - 1] + 1;

        last = nw + 1;
        if (ans[mx_qs] != 0)
            break;
    }

    for (ll i = 0; i < q; ++i)
        cout << ans[qs[i]] << " ";
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t_ = 1; // cin >> t_;
    while (t_--) {
        solve();
        cout << '\n';
    }

    return 0;
}