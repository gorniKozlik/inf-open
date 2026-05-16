#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <map>
#include <cmath>
#include <set>
#define int long long

using namespace std;
using ll = long long;

void solve() {
    ll n, q; cin >> n >> q;
    vector<pair<ll, ll>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    for (int i = 0; i < q; i++) {
        ll x; cin >> x;
        cout << x/2 << " ";
    }
}

signed main() {
    cin.tie(0);
    solve();
    return 0;
}