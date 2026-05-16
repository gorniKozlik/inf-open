#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3", "Ofast", "unroll-loops", "fast-math")
#pragma GCC target("avx", "avx2")

using ll = long long;
using lll = __int128;
using dd = long double;
using para = pair <ll, ll>;
using parad = pair <dd, dd>;
using vll = vector <ll>;
const ll maxn = 401000;
struct f {
    ll max = -1, ind = -1;
};
f merge(const f& a, const f& b) {
    if (a.max > b.max) return a;
    return b;
}
f t[4 * maxn];
ll p[4 * maxn];
void apply(ll v, ll x) {
    t[v].max += x;
    p[v] += x;
}
void push(ll v) {
    if (p[v] == 0) return;
    apply(2 * v + 1, p[v]);
    apply(2 * v + 2, p[v]);
    p[v] = 0;
}
void upd(ll v, ll l, ll r, ll ql, ll qr, ll x) {
    if (l >= qr || r <= ql) return;
    if (l >= ql && r <= qr) {
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
    if (l >= qr || r <= ql) return f{-1, -1};
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
    map <ll, ll> d;
    map <ll, ll> d1;
    for (ll i = 0; i < n; ++i) {
        para x;
        cin >> x.first >> x.second;
        a.push_back(x);
        d[a[i].first]++;
        d[a[i].second]++;
    }
    for (auto& c : d) {
        d1[c.first] = s++;
    }
    for (ll i = 0; i < n; ++i) {
        a[i].first = d1[a[i].first];
        a[i].second = d1[a[i].second];
    }
    for (ll i = 0; i < q; ++i) {
        ll x;
        cin >> x;
        bk.push_back(que{x, i});
    }
    //solve(0, q - 1, 0, n);
    vector <ll> ansk(n + 1, 100000000);
    for (dd i = 0; i < s; i += 0.5) {
        ll x = 0, y = 0;
        ll k = 0;
        for (auto& c : a) {
            if (c.second < i) x++;
            if (c.first > i) y++;
            if (c.first <= i && c.second >= i) k++;
        }
        if (x > y) swap(x, y);
        for (ll j = 0; j <= k; ++j) {
            ansk[j] = 0;
        }
        for (ll j = 1; j <= x; j++) {
            ansk[2 * j + k] = min(ansk[2 * j + k], j);
            ansk[2 * j - 1 + k] = min(ansk[2 * j - 1 + k], j);
        }
    }
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