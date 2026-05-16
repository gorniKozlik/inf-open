
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;
using ll = int;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvll = vector<vll>;
#pragma GCC optimize("O3")
struct SegTree {
    vll tree;
    vll lazy;
    ll n;
    SegTree(ll n) : n(n), tree(4 * n, 1e18) {
    }
    void update(ll i, ll val, ll l, ll r, ll v) {
        if (l == r) {
            tree[v] = min(tree[v], val);
            return;
        }
        ll m = (l + r) >> 1;
        if (i <= m) update(i, val, l, m, 2 * v + 1);
        else update(i, val, m + 1, r, 2 * v + 2);
        tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
    }
    void update(ll i, ll val) {
        update(i, val, 0, n - 1, 0);
    }
    ll get(ll lq, ll rq, ll l, ll r, ll v) {
        if (r < lq || l > rq) return 1e18;
        if (l >= lq && r <= rq) return tree[v];
        ll m = (l + r) >> 1;
        ll le = get(lq, rq, l, m, 2 * v + 1);
        ll ri = get(lq, rq, m + 1, r, 2 * v + 2);
        return min(le, ri);
    }
    ll get(ll lq, ll rq) {
        return get(lq, rq, 0, n - 1, 0);
    }
};
void solve() {
    ll n, q;
    cin >> n >> q;
    vpll a(n);
    ll m = 0;
    for (auto& [l, r] : a) cin >> l >> r;
    {
        set<ll> unique;
        for (ll i = 0; i < n; ++i) unique.insert(a[i].first), unique.insert(a[i].second);
        map<ll, ll> match;
        ll mex = 0;
        for (ll i : unique) match[i] = mex, mex+=2;
        for (auto& [l, r] : a) {
            l = match[l];
            r = match[r];
            m = max(m, r + 1);
        }
        m += 2;
    }
    sort(a.begin(), a.end());
    vll cnt_l(m, 0), cnt_r(m, 0);
    vll le, ri;
    for (auto [l, r] : a) le.push_back(l), ri.push_back(r);
    sort(ri.begin(), ri.end());
    {
    ll j = 1;
    ll pr = 0;
    for (ll i = 0; i < n; ++i) {
        while (j < ri[i]) {
            cnt_l[j] = pr;
            ++j;
        }
        cnt_l[ri[i]] = pr + 1;
        pr = cnt_l[ri[i]];
    }
    for (ll i = 1; i < m; ++i) {
        cnt_l[i] = max(cnt_l[i], cnt_l[i - 1]);
    }
    }
    {
    ll j = 1;
    ll pr = 0;
    for (ll i = 0; i < n; ++i) {
        while (j < le[i]) {
            cnt_r[j] = pr;
            ++j;
        }
        cnt_r[le[i]] = pr + 1;
        pr = cnt_r[le[i]];
    }
    for (ll i = 1; i < m; ++i) {
        cnt_r[i] = max(cnt_r[i], cnt_r[i - 1]);
    }
    }
    
    for (ll _ = 0; _ < q; ++_) {
    ll qi;
    cin >> qi;
    ll answ = 1e9;
    vll add(m + 1, 0);
    for (auto [l, r] : a) {
        add[l]++;
        add[r + 1]--;
    }
    for (ll i = 1; i < m; ++i) {
        add[i] = add[i - 1] + add[i];
    }
    for (ll l = 0; l < m; ++l) {
        ll r = l;
        ll cnt = add[l];
        if (qi <= cnt) {
            answ = min(answ, 0);
            break;
        }
        ll le = l != 0 ? cnt_l[l - 1] : 0, ri = n - cnt_r[r];
        ll tmp = qi - cnt;
        if (tmp <= min(le, ri) * 2) {
            answ = min(answ, (tmp + 1) / 2);
            continue;
        }
        le -= min(le, ri);
        ri -= min(le, ri);
        tmp -= min(le, ri) * 2;
        ll tmp2 = min(le, ri);
        if (le == 0) swap(le, ri);
        if (le >= tmp) {
            answ = min(answ, tmp2 + tmp);
        }
    } 
    cout << answ << ' ';
    }
}

int main() {
    //freopen("in.txt", "r", stdin);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t = 1;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
