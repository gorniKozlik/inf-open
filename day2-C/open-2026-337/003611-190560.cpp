
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
    ll ans = 0;
    vll res(n + 1, 1e18);
    for (ll i = 1; i < n; ++i) {
        res[i] = (i + 1) / 2;
    }
    
    for (ll i = 0; i < q; ++i) {
        ll cnt;
        cin >> cnt;
        cout << res[cnt] << '\n';
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t = 1;
    for (int i = 0; i < t; ++i) {
        solve();
    }
    return 0;
}
