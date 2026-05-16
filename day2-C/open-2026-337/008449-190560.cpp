
#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvll = vector<vll>;

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
        for (ll i : unique) match[i] = mex, mex += 2;
        for (auto& [l, r] : a) {
            l = match[l];
            r = match[r];
            m = max(m, r + 1);
        }
        m += 2;
    }
    sort(a.begin(), a.end());
    for (ll _ = 0; _ < q; ++_) {
    ll qi;
    cin >> qi;
    ll answ = 1e18;
    for (ll l = 0; l < m; ++l) {
        ll r = l;
        vll ans(n + 1, 1e18);
        ll cnt = 0;
        for (ll i = 0; i < n; ++i) {
            if (a[i].first <= l && a[i].second >= r) ++cnt;
        }
        for (ll i = 0; i <= cnt; ++i) ans[i] = 0;
        ll ans_r = cnt;
        ll le = 0, ri = 0;
        for (ll i = 0; i < n; ++i) {
            if (a[i].second < l) ++le;
            if (a[i].first > r) ++ri;
        }
        ll x = 0;
        while (le > 0 && ri > 0) {
            ans[ans_r + 1] = x + 1;
            ans[ans_r + 2] = x + 1;
            x += 1;
            ans_r += 2;
            --le, --ri;
        }
        while (le > 0) {
            ans[ans_r + 1] = x + 1;
            x += 1;
            ans_r += 1;
            --le;
        }
        while (ri > 0) {
            ans[ans_r + 1] = x + 1;
            x += 1;
            ans_r += 1;
            --ri;
        }
        answ = min(answ, ans[qi]);
    } 
    cout << answ << endl;
    }
}

int main() {
   // freopen("in.txt", "r", stdin);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t = 1;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
