#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;

template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll inf = ll(1e18) + 2;
const ll mod = 998244353;

struct node {
    ll x;
    ll p;

    node(ll x_ = -inf, ll p_ = 0) {
        x = x_;
        p = p_;
    }
};

node c(node a, node b) {
    node j;
    j.x = a.x + b.x;
    j.p = 0;
    return j;
}

/*struct st {
    ll n;
    node t[4 * 200001 + 11];

    void build(ll v, vector<ll> &a, ll tl, ll tr) {
        if (tl == tr) {
            t[v].x = a[tl];
            t[v].p = 0;
        } else {
            ll tm = (tl + tr) / 2;
            build(2 * v, a, tl, tm);
            build(2 * v + 1, a, tm + 1, tr);
            t[v] = c(t[2 * v], t[2 * v + 1]);
        }
    }

    node get(ll v, ll tl, ll tr, ll l, ll r) {
        if (l > tr || r < tl || l > r) {
            return {};
        }
        if (tl == l && tr == r) {
            return t[v];
        }
        ll tm = (tl + tr) / 2;
        return c(get(2 * v, ))
    }
};*/

ll bp(ll a, ll n) {
    if (n == 0) {
        return 1 % mod;
    }
    ll k = bp(a, n / 2);
    if (n % 2 == 0) {
        return (k * k) % mod;
    }
    return (((k * k) % mod) * a) % mod;
}

void dfs() {
}

inline void solve() {
    ll n, q;
    cin >> n >> q;
    vector<pair<ll, ll>> a(n);
    for (ll i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a.begin(), a.end());
    vector<ll> b;
    for (auto i: a) {
        b.push_back(i.first);
        b.push_back(i.second);
    }
    sort(b.begin(), b.end());
    vector<ll> p(n + 1, 0);
    ordered_multiset<ll> s;
    ll t2 = 0;
    for (ll i = 0; i < 2 * n; i++) {
        while (t2 < n && a[t2].first <= b[i]) {
            s.insert(a[t2].second);
            t2++;
        }
        ll x = ll(s.size()) - s.order_of_key(*s.lower_bound(b[i]));
        ll x2 = upper_bound(b.begin(), b.end(), b[i]) - b.begin();
        x2 = min(x2, 2 * n - x2);
        p[x2] = max(p[x2], x);
    }
    vector<ll> p2(n + 1, 0);
    p2[n] = p[n];
    for (ll i = n - 1; i > -1; i--) {
        p2[i] = max(p2[i + 1], p[i]);
    }
    vector<ll> ans(q);
    vector<pair<ll, ll> > qs(q);
    for (ll qi = 0; qi < q; qi++) {
        cin >> qs[qi].first;
        qs[qi].second = qi;
    }
    sort(qs.begin(), qs.end());
    for (ll qi = 0; qi < q; qi++) {
        ans[qs[qi].second] = max(0ll, (qs[qi].first - p2[qs[qi].first]));
    }
    for (ll i = 0; i < q; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll q = 1;
    // cin >> q;
    while (q--) {
        solve();
    }
    return 0;
}
