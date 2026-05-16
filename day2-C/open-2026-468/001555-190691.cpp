#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdint>

#pragma GCC optimize("03")

using namespace std;

typedef long long ll;
//typedef unsigned long long ll;
const ll LINF = 1LL << 62LL;
typedef string str;
#define cin(a) for (auto &el : a) cin >> el;
#define cout(a) { for (auto &el : a) { cout << el; } cout << '\n'; }
#define endl "\n"

const ll MOD = 998244353;

ll POW(ll a, ll b, ll mod = MOD) {
    ll r = 1;
    while (b) {
        if (b & 1) r *= a%mod;
        a *= a%mod;
        b >>= 1;
    }
    return r%mod;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<tuple<int, int, int>> v;
    for (int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        v.emplace_back(l, r, i+1);
    }
    while (q--) {
        ll ans = 0;
        int k; cin >> k;
        if (k == 1) ans = 1;
        else ans = (k / 2);
        cout << ans;
    }
    return 0;
}