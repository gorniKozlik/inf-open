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
    ll max = 1000000000;
};
f merge(const f& a, const f& b) {
    if (a.max < b.max) return a;
    return b;
}
f t[4 * maxn];
ll p[4 * maxn];
void apply(ll v, ll x) {
    t[v].max = x;
    p[v] = x;
}
void push(ll v) {
    if (p[v] == -1) return;
    apply(2 * v + 1, p[v]);
    apply(2 * v + 2, p[v]);
    p[v] = -1;
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
    if (l >= qr || r <= ql) return f{1000000000};
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
    for (ll i = 0; i < 4 * maxn; ++i) {
        p[i] = -1;
    }
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
    //solve(0, q - 1, 0, n);
    vector <ll> ansk(n + 1, 100000000);
    ll x = 0;
    ll k = 0;
    ll maxk = 0;
    vector <para> bkx;
    ll maxkxy = -1;
    for (ll i = 0; i < s; i++) {
        k = k - dr[i - 1] + dl[i];
        /*/for (auto& c : a) {
            if (c.second < i) x++;
            if (c.first > i) y++;
        }/*/
        x += dr[i - 1];
        ll y = n - k - x;
        //cout << i << ' ' << k << ' ' << x << ' ' << y << "\n";
        ll xy = min(x, y);
        maxk = max(maxk, k);
        //k + 1, k + 2 * xy;
        ll l = k, r = k + 2 * xy + 1;
        while (r - l > 1) {
            ll m = (l + r) >> 1;
            if (get(0, 0, s, k + 1, m + 1).max <= k) {
                l = m;
            } else {
                r = m;
            }
        }
        if (r <= 2 * xy + k) {
            upd(0, 0, s, r, k + 2 * xy + 1, k);
        }
        /*/bool fl = true;
        for (auto& c : bkx) {
            if (c.first + 2 * c.second >= k + 2 * xy && c.first >= k) {
                fl = false;
                break;
            }
        }
        if (fl) {
            bkx.push_back({k, xy});
            for (ll j = 1; j <= xy; j++) {
                ansk[2 * j + k] = min(ansk[2 * j + k], j);
                ansk[2 * j - 1 + k] = min(ansk[2 * j - 1 + k], j);
            }
        }/*/
            /*/for (auto& ind : bk) {
                if (ind.k >= k + 1 && ind.k <= 2 * xy + k) {
                    ansk[ind.k] = min(ansk[ind.k], (ind.k - k + 1) / 2);
                }
            }/*/
        /*/for (ll j = 1; j <= xy; j++) {
            ansk[2 * j + k] = min(ansk[2 * j + k], j);
            ansk[2 * j - 1 + k] = min(ansk[2 * j - 1 + k], j);
        }/*/
        ll k1 = k - dr[i];
        ll x1 = x + dr[i];
        ll y1 = n - k1 - x1;
        ll xy1 = min(x1, y1);
        //cout << i << ' ' << k << ' ' << x1 << ' ' << y1 << "\n";
        maxk = max(maxk, k1);
        l = k1, r = k1 + 2 * xy1 + 1;
        while (r - l > 1) {
            ll m = (l + r) >> 1;
            if (get(0, 0, s, k1 + 1, m + 1).max <= k1) {
                l = m;
            } else {
                r = m;
            }
        }
        if (r <= 2 * xy1 + k1) {
            upd(0, 0, s, r, k1 + 2 * xy1 + 1, k1);
        }
        /*/fl = true;
        for (auto& c : bkx) {
            if (c.first + 2 * c.second >= k1 + 2 * xy1 && c.first >= k1) {
                fl = false;
                break;
            }
        }
        if (fl) {
            bkx.push_back({k1, xy1});
            for (ll j = 1; j <= xy1; j++) {
                ansk[2 * j + k1] = min(ansk[2 * j + k1], j);
                ansk[2 * j - 1 + k1] = min(ansk[2 * j - 1 + k1], j);
            }
        }/*/
        /*/for (ll j = 1; j <= xy1; j++) {
            ansk[2 * j + k] = min(ansk[2 * j + k], j);
            ansk[2 * j - 1 + k] = min(ansk[2 * j - 1 + k], j);
        }/*/
    }
    for (ll i = 0; i <= maxk; ++i) {
        ansk[i] = 0;
    }
    for (ll i = maxk + 1; i <= n; ++i) {
        ansk[i] = (i - get(0, 0, s, i, i + 1).max + 1) / 2;
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