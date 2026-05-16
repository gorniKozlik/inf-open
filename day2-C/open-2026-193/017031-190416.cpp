#include<iostream>
#include<algorithm>
#include<set>
#include<vector>
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

inline bool cmpl(pair<ll, ll> sl1, pair<ll, ll> sl2) {
    if (sl1.second != sl2.second)
        return sl1.first > sl2.first;
    return sl1.second > sl2.second;
}

inline bool cmpr(pair<ll, ll> sr1, pair<ll, ll> sr2) {
    if (sr1.second != sr2.second)
        return sr1.second < sr2.second;
    return sr1.first < sr2.first;
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

    sort(sl, sl + n, cmpl);
    sort(sr, sr + n, cmpr);

    ans[0] = -1;
    ll k = 0, mx_k = -1;
    vector<ll> ps;
    for (auto& p : st) {
        if (p.second == 1)
            ++k;
        else --k;

        if (k > mx_k) {
            mx_k = k;
            ps = { p.first };
        } else if (k == mx_k)
            ps.emplace_back(p.first);
    }
    ll last = mx_k + 1;

    ll it = 0;
    for (ll i = 0; i < n; ++i) {
        int mn = 2;
        for (auto& nw_ps : ps) {
            int nw_mn = 0;
            if (sl[it].first <= nw_ps) ++nw_mn;
            if (sr[it].second >= nw_ps) ++nw_mn;
            mn = min(mn, nw_mn);
        }
        mx_k += 2 - mn;

        ++it;

        for (ll j = last; j <= mx_k; ++j)
            ans[j] = i + 1;

        last = mx_k + 1;
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
