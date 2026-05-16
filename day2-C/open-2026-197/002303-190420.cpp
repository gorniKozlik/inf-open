#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template<class T>
using oset = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using ll = long long;
ll MOD = 998244353;

void viperr() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll,ll>> a(n);
    vector<ll> b;
    for (auto &[f, s] : a) {
        cin >> f >> s;
        b.push_back(f);
        b.push_back(s);
    }
    sort(b.begin(), b.end());
    vector<ll> pref(2 * n + 1);
    vector<ll> isr(2 * n + 1);
    for (auto &[l, r] : a) {
        l = lower_bound(b.begin(), b.end(), l) - b.begin();
        r = lower_bound(b.begin(), b.end(), r) - b.begin();
        pref[l]++;
        pref[r + 1]--;
        isr[r]++;
    }
    vector<ll> ans(n);
    ll mx = 0, mx2 = 0;
    ll cn = 0;
    for (ll i = 1;i <= 2 * n;i++) {
        pref[i] += pref[i - 1];
        mx = max(mx, pref[i]);
        cn += isr[i];
        ll cnl = n - pref[i] - cn;
        mx2 = max(mx2, min(cnl, cn) * 2 + pref[i] - 1);
    }
    for (ll i = 0;i < mx;i++) {
        ans[i] = 0;
    }
    for (ll i = mx;i < mx2;i++) {
        ans[i] = i / 2;
    }
    for (ll i = mx2;i < n;i++) {
        ans[i] = ans[i - 1] + 1;
    }
    for (ll i = 0;i < q;i++) {
        ll j;
        cin >> j;
        cout << ans[j - 1] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll ttt1 = 1;
    // cin >> ttt1;
    while (ttt1--) {
        viperr();
        cout << '\n';
    }
}