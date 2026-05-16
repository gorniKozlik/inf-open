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
    sort(a.begin(), a.end());
    ll _; cin >> _;
    ll r = n-1, answ = 0;
    for (ll l = 0; l < r; l++) {
        if (a[l].second > a[r].first) continue;
        answ++;
        r--;
    }
    cout << answ;
}

signed main() {
    cin.tie(0);
    solve();
    return 0;
}