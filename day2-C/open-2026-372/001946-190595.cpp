#include<algorithm>
#include <iostream>
#include<set>
#include<map>
#include<unordered_map>
#include<math.h>
#include<cmath>
#include<vector>
#include<queue>
#include<deque>
#include<iomanip>
#include<random>

using namespace std;

//#pragma GCC optimize("O3")
//#pragma GCC target("avx2")

using ll = int;
using ld = long double;
#define all(x) x.begin(), x.end()

struct node {
    ll mx, p, l, r;
};

ll inf = 1e9, mod = 998244353, ql, qr, x;
vector<node> d;

ll binpow(ll a, ll k) {
    ll res = 1;
    while (k) {
        if (k & 1) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}

void push(int h) {
    if (d[h].l == -1) {
        d[h].l = d.size();
        d.push_back({ 0, 0, -1, -1 });
        d[h].r = d.size();
        d.push_back({ 0, 0, -1, -1 });
    }
    d[d[h].l].mx += d[h].p;
    d[d[h].l].p += d[h].p;
    d[d[h].r].mx += d[h].p;
    d[d[h].r].p += d[h].p;
    d[h].p = 0;
}

void add(int h, int l, int r) {
    //cout << l << ' ' << r << ' ' <<h<<' '<<d.size() << '\n';
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        d[h].mx += x;
        d[h].p += x;
        //cout << l << ' ' << r << '\n';
        return;
    }
    int m = (l + r) / 2;
    push(h);
    add(d[h].l, l, m);
    add(d[h].r, m + 1, r);
    d[h].mx = max(d[d[h].l].mx, d[d[h].r].mx);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n, q, mx = 0, t = 0, l1, r1, l2, r2, k = 1;
    x = 1;
    cin >> n >> q;
    set<pair<ll, ll>> l, r;
    d.reserve(2e8);
    d.push_back({ 0, 0, -1, -1 });
    vector<ll> ans(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> ql >> qr;
        l.insert({ qr, ql });
        r.insert({ ql, qr });
        add(0, 1, 1e9);
    }
    t = d[0].mx + 1;
    pair<ll, ll> lf, rf;
    while (t <= n) {
        lf = *l.begin();
        l.erase(l.begin());
        r.erase({ lf.second, lf.first });
        rf = *--r.end();
        r.erase(--r.end());
        l.erase({ rf.second, rf.first });
        l1 = lf.second, r1 = lf.first, l2 = rf.first, r2 = rf.second;
        //cout << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << '\n';
        x = -1;
        ql = l1, qr = r1;
        add(0, 1, 1e9);
        ql = l2, qr = r2;
        add(0, 1, 1e9);
        ql = l1, qr = l2, x = 1;
        add(0, 1, 1e9);
        ql = r1, qr = r2;
        add(0, 1, 1e9);
        for (int i = t; i <= d[0].mx; ++i) ans[i] = k;
        ++k;
        t = d[0].mx + 1;
    }
    while (q--) {
        cin >> t;
        cout << ans[t] << ' ';
    }
}

