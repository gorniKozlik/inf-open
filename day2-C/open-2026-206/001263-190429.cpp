#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using vll = vector<ll>;

const ll nmax = 2e5 + 1;
ll ans[nmax];

vector<pll> a;
vector<ll> all;

ll get_ans() {
    ll res = 0;
    for (ll &p: all) {
        ll cnt = 0;
        for (auto &[l, r]: a)
            cnt += (l <= p && p <= r);
        res = max(res, cnt);
    }
    return res;
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
    }

    sort(a.begin(), a.end());
    sort(all.begin(), all.end());

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
            for (ll j = 0; j < n; j++) {
                auto [l1, r1] = a[i];
                auto [l2, r2] = a[j];

                a[i] = {l1, l2};
                a[j] = {r1, r2};

                ll suspect = get_ans();
                if (suspect > best) {
                    best = suspect;
                    ibest = i;
                    jbest = j;
                }

                a[i] = {l1, r1};
                a[j] = {l2, r2};
            }
        }

        if (ibest == -1 && jbest == -1)
            break;

        auto [l1, r1] = a[ibest];
        auto [l2, r2] = a[jbest];

        a[ibest] = {l1, l2};
        a[jbest] = {r1, r2};
    }

    for (ll i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
