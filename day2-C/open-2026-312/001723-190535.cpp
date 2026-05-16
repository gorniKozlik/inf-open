#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct edge {
    ll cur;
    ll prev;
    ll next;
};

int main() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> a(n);
    vector<ll> val;
    for (auto &[x, y] : a) {
        cin >> x >> y;
        val.push_back(x);
        val.push_back(y);
    }
    sort(val.begin(), val.end());
    val.resize(unique(val.begin(), val.end()) - val.begin());
    ll sz = (ll) val.size();
    vector<ll> beg(sz), en(sz);
    for (auto &[x, y] : a) {
        x = lower_bound(val.begin(), val.end(), x) - val.begin();
        y = lower_bound(val.begin(), val.end(), y) - val.begin();
        beg[x]++;
        en[y]++;
    }
    vector<edge> c;
    ll cntb = 0, cnte = 0;
    for (ll i = 0; i < sz; i++) {
        cntb += beg[i];
        cnte += en[i];
        ll cur = cntb - cnte;
        c.push_back({cur, cnte, n - cur - cnte});
    }
    sort(c.begin(), c.end(), [] (edge &A, edge &B) {
        return A.cur > B.cur;
    });
    vector<ll> ans(n + 1, 1e9);
    ll last = 1;
    for (ll i = 0; i < sz; i++) {
        auto [cur, prev, next] = c[i];
        // if (i == 5) cout << cur << ' ' << prev << ' ' << next << '\n';
        for (ll j = last; j <= cur; j++) ans[j] = 0;
        last = max(last, cur + 1);
        ll mx = min(prev, next);
        for (ll j = last; j <= min(n, cur + 2 * mx); j++) {
            ll op = (j - cur + 1) / 2;
            ans[j] = op;
            last = j + 1;
        }
        // if (i == 5) {
        //     for (ll j : ans) cout << j << ' ';
        //     cout << '\n';
        //     cout << last << '\n';
        // }
    }
    while (q--) {
        ll x;
        cin >> x;
        cout << ans[x] << ' ';
    }
    cout << '\n';
}
