#ifdef LOCAL
#define GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

constexpr ll mod = 998244353;

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
    }
    sort(pn.begin(), pn.end());
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
    for (int i = n; i > 0; --i) {
        if (ans[i] == 1e18) {
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