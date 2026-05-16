#include <bits/stdc++.h>
#include <experimental/random>

using namespace std;
using ll = long long;
using ld = long double;

const ll INF = 2e18, MOD = 998244353;

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int q = 1;
    // cin >> q;
    while (q--) {
        solve();
    }
}

void solve() {
    ll n, q;
    cin >> n >> q;
    vector<ll> cord;
    vector<pair<ll, ll>> seg;
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        cord.push_back(l), cord.push_back(r);
        seg.emplace_back(l, r);
    }
    sort(cord.begin(), cord.end());
    cord.resize(unique(cord.begin(), cord.end()) - cord.begin());

    for (auto &[l, r] : seg) {
        l = lower_bound(cord.begin(), cord.end(), l) - cord.begin();
        r = lower_bound(cord.begin(), cord.end(), r) - cord.begin();
    }

    ll m = (int)cord.size();
    vector<ll> p(m + 1), s(m + 1);
    for (auto [l, r] : seg) {
        p[r + 1]++;
        s[l]++;
    }
    for (int i = 1; i <= m; i++) {
        p[i] += p[i - 1];
    }
    for (int i = m - 1; i >= 0; i--) {
        s[i] += s[i + 1];
    }

    ll mx = -1;
    vector<ll> mm(8 * m, -INF);
    vector<ll> mn(8 * m, INF);
    for (int i = 0; i < m; i++) {
        ll x = p[i], y = s[i + 1];
        mx = max(mx, n - x - y);
        mm[2 * min(x, y) + (n - x - y)] = max(mm[2 * min(x, y) + (n - x - y)], n - x - y);

    }

    for (ll i = 8 * m - 2; i >= 0; i--) {
        mm[i] = max(mm[i], mm[i + 1]);
    }

    while (q--) {
        ll k; cin >> k;
        if (mx >= k) {
            cout << 0 << ' ';
            continue;
        }
        if (mm[k] != -INF) {
            cout << (k - mm[k] + 1) / 2 << ' ';
            continue;
        }
        ll ans = INF;
        for (int i = 0; i < m; i++) {
            ll x = p[i], y = s[i + 1];
            ll ost = k - (n - x - y) - 2 * min(x, y);
            if (x > y) {
                ll c = x - y;
                ll c2 = s[i] - s[i + 1];
                if (min(c, c2) >= ost) {
                    ans = min(ans, min(x, y) + ost);
                }
            } else {
                ll c = y - x;
                ll c2 = p[i + 1] - p[i];
                if (min(c, c2) >= ost) {
                    ans = min(ans, min(x, y) + ost);
                }
            }
        }
        cout << ans << ' ';
    }

}