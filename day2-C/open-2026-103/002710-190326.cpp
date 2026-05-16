#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
using vl = __int128_t;
using ld = long double;
using ul = unsigned long long;
using ordered_set = tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>;
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define sz(a) (ll)a.size()
const ll mod = 998244353;
ll pw(ll a, ll b) {
    ll r = 1;
    while (b) {
        if (b & 1) r = (r * a) % mod;
        a = (a * a) % mod, b >>= 1;
    }
    return r;
}
ll f(ll x, ll k, vector<pair<ll, ll>>& a) {
    ll lt = 0, rt = 0, pr = 0;
    for (auto [l, r] : a) {
        if (r < x) lt++;
        else if (l > x) rt++;
        else pr++;
    }
    k -= pr;
    if (k < 1) return 0;
    if (min(lt, rt) * 2 >= k) return (k + 1) / 2;
    k -= min(lt,  rt) * 2;
    return min(lt, rt) + max(lt, rt) - min(lt, rt);
}
void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> a(n);
    for (auto& [l, r] : a) cin >> l >> r;
    while (q--) {
        ll k;
        cin >> k;
        ll ans = 1e18;
        for (auto [l, r] : a) {
            ans = min(ans, f(l, k, a));
        }
        cout << ans << ' ';
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
