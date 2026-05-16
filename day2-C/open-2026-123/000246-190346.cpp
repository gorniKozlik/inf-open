#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;


#define all(v) begin(v), end(v)
#define rall(v) rbegin(v), rend(v)
#define FOR(i, a, b) for(ll i = a; i < b; ++i)
#define ROF(i, a, b) for(ll i = b; i >= a; --i)

mt19937 rnd(42);
mt19937_64 rnd64(52);

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll n, q;
    cin >> n >> q;
    vector<pair<ll,ll>> v(n);
    vector<ll> v2(2 * n);
    for (ll i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
        v2[i * 2] = v[i].first;
        v2[i * 2 + 1] = v[i].second;
    }
    sort(all(v2));
    for (ll i = 0; i < n; ++i) {
        v[i].first = lower_bound(v2.begin(), v2.end(), v[i].first) - v2.begin();
        v[i].second = lower_bound(v2.begin(), v2.end(), v[i].second) - v2.begin();
    }
    for (ll i = 0; i < q; ++i) {
        ll k; cin >> k;
        cout << k / 2 << " ";
    }
}