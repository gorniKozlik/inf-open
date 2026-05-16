#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll INF = 2e18;

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll> > a(n);
    map<ll, pair<ll, ll> > mp;
    for (auto &&[u,v]: a) {
        cin >> u >> v;
        mp[u].first += 1;
        mp[v + 1].second += 1;
    }
    ll cur = 0, vis = 0;
    vector<ll> ans(n + 1);
    for (auto &&[u,v]: mp) {
        cur += v.first;
        cur -= v.second;
        vis += v.second;
        ll ost = n - cur - vis;
        // cerr << u << ' ' << cur << ' ' << vis << ' ' << ost << '\n';
        ll can = min(ost, vis);
        ans[cur + can * 2] = max(ans[cur + can * 2], cur);
    }
    // for (auto &i: ans) cerr << i << ' ';
    // cerr << '\n';
    vector<ll> res(n + 1);
    ll mx = 0;
    for (int i = n; i > 0; --i) {
        mx = max(mx, ans[i]);
        res[i] = min<ll>(i, mx);
    }
    vector<ll> qs(q);
    for (auto &i: qs) {
        cin >> i;
        cout << (i - res[i] + 1) / 2 << ' ';
    }
    cout << '\n';
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef LOCAL
    freopen("input", "r", stdin);
    freopen("output", "w", stdout);
#endif
    solve();
}
