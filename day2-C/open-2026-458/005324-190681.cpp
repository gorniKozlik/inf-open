#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;

bool comp(const pair<ll, ll>& a, const pair<ll, ll>& b) {
    if (a.first == b.first) return a.second > b.second;
    return a.first < b.first;
}

ll cnt(set<pair<ll, ll>> v) {
    vector<pair<ll, ll>> event;
    for (auto [i, j] : v) {
        event.push_back({i, 1});
        event.push_back({j, -1});
    }
    sort(event.begin(), event.end(), comp);
    ll ans = 0;
    ll temp = 0;
    for (ll i = 0; i < event.size(); i++) {
        temp += event[i].second;
        ans = max(ans, temp);
    }
    return ans;
}

void solve() {
    ll n, q;
    cin >> n >> q;
    set<pair<ll, ll>> v;
    for (ll i = 0; i < n; i++) {
        ll a, b;
        cin >> a >> b;
        v.insert({a, b});
    }
    vector<ll> ans(n+1, -1);
    ll res = cnt(v);
    for (ll i = 0; i <= res; i++) {
        ans[i] = 0;
    }
    ll prev = res+1;
    for (ll k = 0; k < n; k++) {
        for (auto [i, j] : v) {
            auto it = v.rbegin();
            while ((*it).first < j && it != v.rend()) it++;
            if (it != v.rend()) {
                pair<ll, ll> p = *it;
                cout << i << ' ' << j << ' ' << p.first << ' ' << p.second << '\n';
                v.insert({j, p.first});
                v.insert({i, p.second});
                v.erase({i, j});
                v.erase(p);
                break;
            }
        }
        res = cnt(v);
        for (ll j = prev; j <= res; j++) {
            ans[j] = k+1;
        }
        prev = res+1;
        if (prev == n+1) break;
    }
    for (ll i = 0; i < q; i++) {
        ll k;
        cin >> k;
        cout << ans[k] << ' ';
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //ios_base::sync_with_stdio(false); cin.tie(0);
    ll t = 1;
    //cin >> t;
    while(t--) solve();

    return 0;
}
