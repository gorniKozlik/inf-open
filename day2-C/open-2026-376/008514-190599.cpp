#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ll n, q;
    cin >> n >> q;

    vector<ll> l(n), r(n);
    vector<ll> ps;
    for (ll i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        ps.push_back(l[i]);
        ps.push_back(r[i]);
    }

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    sort(ps.begin(), ps.end());
    vector<ll> cur(2 * n), mx(2 * n);
    for (ll i = 0; i < 2 * n; i++) {
        ll ls_l = upper_bound(l.begin(), l.end(), ps[i]) - l.begin();
        ll ls_r = upper_bound(r.begin(), r.end(), ps[i]) - r.begin();
        cur[i] = ls_l - ls_r;
        mx[i] = min(i + 1, 2 * n - i - 1);
    }

    vector<ll> mx_suff(n + 1);
    for (ll i = 0; i < n * 2; i++) {
        mx_suff[mx[i]] = max(mx_suff[mx[i]], cur[i]);
    }
    for (ll i = n - 1; i >= 0; i--) {
        mx_suff[i] = max(mx_suff[i], mx_suff[i + 1]);
    }

    vector<ll> ans(n + 1);
    for (ll i = 0; i <= n; i++) {
        ans[i] = max(0ll, i - mx_suff[i] + 1) / 2;
    }

    while (q--) {
        ll k;
        cin >> k;

        cout << ans[k] << ' ';
    }
    cout << '\n';
}