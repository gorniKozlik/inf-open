#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, q;
    cin >> n >> q;
    set<pair<ll, ll> > sl, sr;
    while (n--) {
        ll l, r;
        cin >> l >> r;
        sl.emplace(l, r);
        sr.emplace(r, l);
    }
    ll ans = 0;
    while (1) {
        auto il = sl.end();
        il--;
        auto l = *il;
        auto ir = sr.begin();
        auto r = *ir;
        if (l.first < r.first) {
            break;
        }
        ans++;
        pair<ll, ll> nl = {r.first, l.first}, nr = {r.second, l.second};
        sl.erase(l);
        sl.erase({r.second, r.first});
        sr.erase({l.second, l.first});
        sr.erase(r);
        sl.emplace(nl);
        sl.emplace(nr);
        sr.emplace(nl.second, nl.first);
        sr.emplace(nr.second, nr.first);
    }
    cout << ans;
}
