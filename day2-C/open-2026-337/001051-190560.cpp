
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
    for (auto& [l, r] : a) cin >> l >> r;
    {
        set<ll> unique;
        for (auto [l, r] : a) unique.insert(l), unique.insert(r);
        map<ll, ll> match;
        ll mex = 0;
        for (ll i : unique) match[i] = mex, ++mex;
        for (auto& [l, r] : a) l = match[l], r = match[r];
    }
    sort(a.begin(), a.end());
    vpll event;
    for (ll i = 0; i < n; ++i) {
        event.push_back({a[i].first, 1});
        event.push_back({a[i].second + 1, -1});
    }
    sort(event.begin(), event.end());
    ll cnt = 0;
    ll ans = 0;
    for (auto [x, t] : event) {
        cnt += t;
        ans = max(ans, cnt);
    }
    vll res(n + 1);
    for (ll i = 0; i <= ans; ++i) {
        res[i] = 0;
    }
    for (ll i = 0; i < q; ++i) {
        ll cnt;
        cin >> cnt;
        cout << res[cnt] << '\n';
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
