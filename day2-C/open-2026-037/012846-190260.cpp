#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3", "Ofast", "unroll-loops", "fast-math")
#pragma GCC target("avx", "avx2")

using ll = int;
using lll = __int128;
using dd = long double;
using para = pair <ll, ll>;
using parad = pair <dd, dd>;
using vll = vector <ll>;
const ll maxn = 401000;
struct f {
    ll max = 0, min = 1000000000;
};
f merge(const f& a, const f& b) {
    return f{max(a.max, b.max), min(a.min, b.min)};
}
f t[4 * maxn];
ll p[4 * maxn];
void build(ll v, ll l, ll r) {
    p[v] = -1;
    if (l + 1 == r) {
        t[v].max = 0;
        t[v].min = 0;
        return;
    }
    ll m = (l + r) >> 1;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    t[v] = merge(t[2 * v + 1], t[2 * v + 2]);
}
void apply(ll v, ll x) {
    t[v].max = x;
    t[v].min = x;
    p[v] = x;
}
void push(ll v) {
    if (p[v] == -1) return;
    apply(2 * v + 1, p[v]);
    apply(2 * v + 2, p[v]);
    p[v] = -1;
}
void upd(ll v, ll l, ll r, ll ql, ll qr, ll x) {
    if (l >= qr || r <= ql || t[v].min >= x) return;
    if (l >= ql && r <= qr && t[v].max <= x) {
        apply(v, x);
        return;
    }
    push(v);
    ll m = (l + r) >> 1;
    upd(2 * v + 1, l, m, ql, qr, x);
    upd(2 * v + 2, m, r, ql, qr, x);
    t[v] = merge(t[2 * v + 1], t[2 * v + 2]);
}
f get(ll v, ll l, ll r, ll ql, ll qr) {
    if (l >= qr || r <= ql) return f{0, 1000000000};
    if (l >= ql && r <= qr) return t[v];
    push(v);
    ll m = (l + r) >> 1;
    return merge(get(2 * v + 1, l, m, ql, qr), get(2 * v + 2, m, r, ql, qr));
}
struct que {
    ll k, ind;
};
bool operator<(const que& a, const que& b) {return a.k < b.k;}
vector <que> bk;
vector <para> a;
void solvetask() {
    ll n, q;
    cin >> n >> q;
    ll s = 0;
    unordered_map <ll, ll> d1;
    vector <ll> sor;
    for (ll i = 0; i < n; ++i) {
        para x;
        cin >> x.first >> x.second;
        a.push_back(x);
        sor.push_back(x.first);
        sor.push_back(x.second);
        //d[a[i].first]++;
        //d[a[i].second]++;
    }
    sort(sor.begin(), sor.end());
    for (ll i = 0; i < sor.size(); ++i) {
        d1[sor[i]] = s++;
    }
    build(0, 0, n + 1);
    vector <ll> dl(s);
    vector <ll> dr(s);
    for (ll i = 0; i < n; ++i) {
        a[i].first = d1[a[i].first];
        a[i].second = d1[a[i].second];
        dl[a[i].first]++;
        dr[a[i].second]++;
    }
    for (ll i = 0; i < q; ++i) {
        ll x;
        cin >> x;
        bk.push_back(que{x, i});
    }
    vector <ll> ansk(n + 1, 100000000);
    ll x = 0;
    ll k = 0;
    ll maxk = 0;
    for (ll i = 0; i < s; i++) {
        k = k - (i >= 1 ? dr[i - 1] : 0) + dl[i];
        x += (i >= 1 ? dr[i - 1] : 0);
        ll y = n - k - x;
        ll xy = min(x, y);
        maxk = max(maxk, k);
        upd(0, 0, n + 1, k + 1, k + 2 * xy + 1, k);
        /*/ll l = k, r = k + 2 * xy + 1;
        while (r - l > 1) {
            ll m = (l + r) >> 1;
            if (get(0, 0, n + 1, k + 1, m + 1).max < k) {
                l = m;
            } else {
                r = m;
            }
        }
        cout << i << ' ' << k << ' ' << k + 2 * xy << "\n";
        if (l >= k + 1) {
            upd(0, 0, n + 1, k + 1, l + 1, k);
        }/*/
        ll k1 = k - dr[i];
        ll x1 = x + dr[i];
        ll y1 = n - k1 - x1;
        ll xy1 = min(x1, y1);
        maxk = max(maxk, k1);
        upd(0, 0, n + 1, k1 + 1, k1 + 2 * xy1 + 1, k1);
        /*/cout << i << ' ' << k1 << ' ' << k1 + 2 * xy1 << "\n";
        l = k1, r = k1 + 2 * xy1 + 1;
        while (r - l > 1) {
            ll m = (l + r) >> 1;
            if (get(0, 0, n + 1, k1 + 1, m + 1).max < k1) {
                l = m;
            } else {
                r = m;
            }
        }
        if (l >= k1 + 1) {
            upd(0, 0, n + 1, k1 + 1, l + 1, k1);
        }/*/
    }
    for (ll i = 0; i <= maxk; ++i) {
        ansk[i] = 0;
    }
    for (ll i = maxk + 1; i <= n; ++i) {
        //cout << i << ' ' << get(0, 0, n + 1, i, i + 1).max << '\n';
        ansk[i] = (i - get(0, 0, n + 1, i, i + 1).max + 1) / 2;
    }
    //cout << "\n";
    for (ll i = 0; i < q; ++i) {
        cout << ansk[bk[i].k] << " ";
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll tests = 1;
    //cin >> tests;
    while (tests--) {
        solvetask();
    }
    return 0;
}