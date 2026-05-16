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
    vector<ll> pn;
    for (auto [l, r] : seg) {
        pn.emplace_back(l);
        pn.emplace_back(r);
    }
    sort(pn.begin(), pn.end());
    ll ls = pn[n - 1], rs = pn[n];
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        if (seg[i].first > ls || seg[i].second < rs) {
            ans++;
        }
    }
    cout << ans / 2;
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