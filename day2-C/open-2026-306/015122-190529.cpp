#ifdef LOCAL
#define GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

constexpr ll mod = 998244353;

struct Segtree {
    vector<ll> t;
    ll size = 1;

    void init(ll n) {
        while (size < n) {
            size *= 2;
        }
        t.resize(size * 2 - 1);
    }

    ll merge(ll l, ll r) {
        return l + r;
    }

    void set(ll v, ll x, ll i, ll l, ll r) {
        if (r - l == 1) {
            t[v] = x;
            return;
        }
        ll m = (l + r) / 2;
        if (i < m) {
            set(v * 2 + 1, x, i, l, m);
        } else {
            set(v * 2 + 2, x, i, m, r);
        }
        t[v] = merge(t[v * 2 + 1], t[v * 2 + 2]);
    }
    void set(ll x, ll i) {
        set(0, x, i, 0, size);
    }

    ll get(ll v, ll tl, ll tr, ll ql, ll qr) {
        if (tl >= qr || tr <= ql) {
            return 0;
        }
        if (tl >= ql && tr <= qr) {
            return t[v];
        }
        ll tm = (tl + tr) / 2;
        return merge(get(v * 2 + 1, tl, tm, ql, qr), get(v * 2 + 2, tm, tr, ql, qr));
    }
    ll get(ll l, ll r) {
        return get(0, 0, size, l, r);
    }
};

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> seg(n);
    for (int i = 0; i < n; ++i) {
        cin >> seg[i].first >> seg[i].second;
    }
    vector<pair<ll, ll>> ask(q);
    for (int i = 0; i < q; ++i) {
        cin >> ask[i].first;
        ask[i].second = i;
    }
    sort(ask.begin(), ask.end());
    vector<pair<ll, ll>> pn;
    vector<ll> comp;
    for (auto [l, r] : seg) {
        pn.emplace_back(l, 1);
        pn.emplace_back(r, -1);
        comp.emplace_back(l);
        comp.emplace_back(r);
    }
    sort(pn.begin(), pn.end());
    sort(comp.begin(), comp.end());
    comp.resize(unique(comp.begin(), comp.end()) - comp.begin());
    for (auto& [x, i] : pn) {
        x = lower_bound(comp.begin(), comp.end(), x) - comp.begin();
    }
    for (auto& [l, r] : seg) {
        l = lower_bound(comp.begin(), comp.end(), l) - comp.begin();
        r = lower_bound(comp.begin(), comp.end(), r) - comp.begin();
    }
    ll cntl = 0, cntr = 0, cur = 0;
    vector<ll> ls(n * 2), rs(n * 2);
    for (int i = 0; i < pn.size(); ++i) {
        auto [x, t] = pn[i];
        rs[i] = cntr;
        ls[i] = n - cntl;
        if (t == -1) {
            cntr++;
            cur--;
        } else {
            cntl++;
            cur++;
            ls[i]--;
        }
    }
    vector<pair<ll, ll>> nws;
    for (int i = 1; i < 2 * n; ++i) {
        nws.emplace_back(pn[i - 1].first, pn[i].first);
    }
    vector<ll> ans(n + 1, 1e18);
    ans[1] = 0;
    for (auto [l, r] : nws) {
        ll br = 0, al = 0, in = 0;
        //cout << l << ' ' << r << "   ";
        for (auto [sl, sr] : seg) {
            if (sl <= l && sr >= r) {
                in++;
            }
            if (sr < r) {
                br++;
            }
            if (sl < r) {
                br++;
            }
            if (sl > l) {
                al++;
            }
            if (sr > l) {
                al++;
            }
        }
        //cout << in << ' ' << br << ' ' << al << '\n';
        ans[in] = 0;
        for (int i = 0; i <= min(al, br) - in; ++i) {
            ans[in + i] = min(ans[in + i], (i + 1) / 2ll);
        }
    }
    ll f = 0;
    for (int i = n; i >= 0; --i) {
        if (ans[i] > n) {
            exit(52);
        }
        if (ans[i] == 0) {
            f = 1;
        }
        if (f == 1) {
            ans[i] = 0;
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[ask[i].first] << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll tt = 1;
    //cin >> tt;
    while (tt--) {
        solve();
        cout << endl;
    }
}