#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;

const ll nmax = 2e5 + 1;
const ll nlog = 23;
const ll sz = 1 << nlog;

ll add[sz << 1], st[sz << 1];
ll ans[nmax];

vector<pll> a;
vector<ll> all;

ll f(ll x) {
    return lower_bound(all.begin(), all.end(), x) - all.begin();
}

void push(ll x, ll lx, ll rx) {
    if (rx - lx == 1 || !add[x])
        return;

    add[x << 1] += add[x];
    add[x << 1 | 1] += add[x];

    st[x << 1] += add[x];
    st[x << 1 | 1] += add[x];

    add[x] = 0;
}

ll get_ans() {
    return st[1];
}

void upd(ll ql, ll qr, ll qx, ll x = 1, ll lx = 0, ll rx = sz) {
    if (rx <= ql || lx >= qr) return;
    if (ql <= lx && rx <= qr) {
        add[x] += qx;
        st[x] += qx;
        return;
    }

    push(x, lx, rx);
    ll mid = (lx + rx) / 2;
    upd(ql, qr, qx, x << 1, lx, mid);
    upd(ql, qr, qx, x << 1 | 1, mid, rx);
    st[x] = max(st[x << 1], st[x << 1 | 1]);
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, q;
    cin >> n >> q;
    for (ll i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        a.emplace_back(l, r);
        all.push_back(l);
        all.push_back(r);

        upd(l, r, 1);
    }

    sort(a.begin(), a.end());
    sort(all.begin(), all.end());

    for (auto &[l, r]: a) {
        l = f(l);
        r = f(r);
    }

    vector<pll> quest;
    for (ll i = 0; i < q; i++) {
        ll t;
        cin >> t;
        quest.push_back({t, i});
    }

    ll ptr = 0;
    sort(quest.begin(), quest.end());
    for (ll tm = 0; tm < q; tm++) {
        ll res = get_ans();
        while (ptr < quest.size() && res >= quest[ptr].first)
            ans[quest[ptr++].second] = tm;

        ll best = LLONG_MIN;
        ll ibest = -1, jbest = -1;
        for (ll i = 0; i < n; i++) {
            for (ll j = i + 1; j < n; j++) {
                auto [l1, r1] = a[i];
                auto [l2, r2] = a[j];

                upd(r1, l2, 2);

                ll suspect = get_ans();
                if (suspect > best) {
                    best = suspect;
                    ibest = i;
                    jbest = j;
                }

                upd(r1, l2, -2);
            }
        }

        if (ibest == -1 && jbest == -1)
            break;

        auto [l1, r1] = a[ibest];
        auto [l2, r2] = a[jbest];

        upd(r1, l2, 2);
        a[ibest] = {l1, l2};
        a[jbest] = {r1, r2};
        sort(a.begin(), a.end());
    }

    for (ll i = 0; i < q; i++)
        cout << ans[i] << '\n';
}