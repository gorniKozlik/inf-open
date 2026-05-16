#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;

const ll nmax = 5e5 + 1;
ll d[nmax], ans[nmax];
vector<ll> all;
ll n, q;

ll get(vector<pll> &a) {
    for (ll i = 0; i <= 2 * n; i++)
        d[i] = 0;
    for (auto &[l, r]: a) {
        d[l]++;
        d[r + 1]--;
    }

    ll mx = d[0];
    for (ll i = 1; i < 2 * n; i++) {
        d[i] += d[i - 1];
        mx = max(mx, d[i]);
    }

    return mx;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    vector<pll> a(n);
    for (auto &[l, r]: a) {
        cin >> l >> r;
        all.push_back(l);
        all.push_back(r);
    }

    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());

    for (auto &[l, r]: a) {
        l = lower_bound(all.begin(), all.end(), l) - all.begin();
        r = lower_bound(all.begin(), all.end(), r) - all.begin();
    }

    vector<pll> qs(q);
    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;
        qs[i] = {t, i};
    }

    sort(qs.begin(), qs.end());

    ll ptr = 0;
    ll mx = get(a);
    while (ptr < q && mx >= qs[ptr].first)
        ans[qs[ptr++].second] = 0;

    ll tm = 1;
    while (ptr < q) {
        ll best = 0, ibest = -1, jbest = -1;
        for (ll i = 0; i < n; i++) {
            for (ll j = 0; j < n; j++) {
                if (i == j) continue;
                auto [l1, r1] = a[i];
                auto [l2, r2] = a[j];

                a[i] = {l1, l2};
                a[j] = {r1, r2};

                ll res = get(a);
                if (res > best) {
                    best = res;
                    ibest = i;
                    jbest = j;
                }

                a[i] = {l1, r1};
                a[j] = {l2, r2};
            }
        }

        assert(ibest != -1);
        assert(jbest != -1);

        auto [l1, r1] = a[ibest];
        auto [l2, r2] = a[jbest];

        a[ibest] = {l1, l2};
        a[jbest] = {r1, r2};

        while (ptr < q && best >= qs[ptr].first)
            ans[qs[ptr++].second] = tm;
        tm++;
    }

    for (ll i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
